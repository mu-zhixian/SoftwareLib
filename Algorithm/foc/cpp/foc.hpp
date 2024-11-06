#ifndef __FOC_H_
#define __FOC_H_

#include <cmath>
#include <cstdint>

template<class T>
class FOC{
public:
	void clarke(){
		// sqrt(3)/3 = 0.5773502691896257
		i_alpha = i_a;
		i_beta = (i_a + 2 * i_b) * 0.5773502691896257f;
	}
	void park(){
		sine = sin(theta);
		cosine = cos(theta);
		i_d = i_alpha * cosine + i_beta * sine;
		i_q = i_beta * cosine - i_alpha * sine;
	}
	void ipark(){
		sine = sin(theta);
		cosine = cos(theta);
		u_alpha = u_d * cosine - u_q * sine;
		u_beta = u_q * cosine + u_d * sine;
	}
	void svpwm(){
		//iclarke
		// sqrt(3)/2 = 0.8660254037844386
		// float u2 = -0.8660254037844386 * u_alpha - u_beta / 2;
		// float u3 = 0.8660254037844386 * u_alpha - u_beta / 2;
		constexpr T ts = 1;
		T u1 = u_beta;
		T tmp1 = 0.8660254037844386 * u_alpha;
		T tmp2 = u_beta / 2;
		T u2 = -tmp1 - tmp2;
		T u3 = tmp1 - tmp2;
		unsigned char sector = (u1>0.0) | ((u2>0.0) << 1) | ((u3>0.0) << 2);

		if (sector == 5) {
			T t4 = u3;
			T t6 = u1;
			T sum = t4 + t6;
			if (sum > ts) {
				k_svpwm = ts / sum;
				t4 = k_svpwm * t4;
				t6 = k_svpwm * t6;
			}
			T t7 = (ts - t4 - t6) / 2;
			t_a = t4 + t6 + t7;
			t_b = t6 + t7;
			t_c = t7;
		} else if (sector == 1) {
			T t2 = -u3;
			T t6 = -u2;
			T sum = t2 + t6;
			if (sum > ts) {
				k_svpwm = ts / sum;
				t2 = k_svpwm * t2;
				t6 = k_svpwm * t6;
			}
			T t7 = (ts - t2 - t6) / 2;
			t_a = t6 + t7;
			t_b = t2 + t6 + t7;
			t_c = t7;
		} else if (sector == 3) {
			T t2 = u1;
			T t3 = u2;
			T sum = t2 + t3;
			if (sum > ts) {
				k_svpwm = ts / sum;
				t2 = k_svpwm * t2;
				t3 = k_svpwm * t3;
			}
			T t7 = (ts - t2 - t3) / 2;
			t_a = t7;
			t_b = t2 + t3 + t7;
			t_c = t3 + t7;
		} else if (sector == 2) {
			T t1 = -u1;
			T t3 = -u3;
			T sum = t1 + t3;
			if (sum > ts) {
				k_svpwm = ts / sum;
				t1 = k_svpwm * t1;
				t3 = k_svpwm * t3;
			}
			T t7 = (ts - t1 - t3) / 2;
			t_a = t7;
			t_b = t3 + t7;
			t_c = t1 + t3 + t7;
		} else if (sector == 6) {
			T t1 = u2;
			T t5 = u3;
			T sum = t1 + t5;
			if (sum > ts) {
				k_svpwm = ts / sum;
				t1 = k_svpwm * t1;
				t5 = k_svpwm * t5;
			}
			T t7 = (ts - t1 - t5) / 2;
			t_a = t5 + t7;
			t_b = t7;
			t_c = t1 + t5 + t7;
		} else if (sector == 4) {
			T t4 = -u2;
			T t5 = -u1;
			T sum = t4 + t5;
			if (sum > ts) {
				k_svpwm = ts / sum;
				t4 = k_svpwm * t4;
				t5 = k_svpwm * t5;
			}
			T t7 = (ts - t4 - t5) / 2;
			t_a = t4 + t5 + t7;
			t_b = t7;
			t_c = t5 + t7;
		}
	}

public:
	T u_alpha;
	T u_beta;
	T u_d;
	T u_q;

	T i_alpha;
	T i_beta;
	T i_d;
	T i_q;
	T theta;
	
	T i_a;
	T i_b;
	T i_c;
	T t_a;
	T t_b;
	T t_c;

private:
	T sine;
	T cosine;
	T k_svpwm;
};

#endif /* __FOC_H_ */
