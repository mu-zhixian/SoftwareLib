#include "foc.h"

void InitFOC(FOC* f){

}

void Clarke(FOC* f){
  // sqrt(3)/3 = 0.5773502691896257
  f->i_alpha = f->i_a;
  f->i_beta = (f->i_a + 2 * f->i_b) * 0.5773502691896257f;
}

void Park(FOC* f){
  f->sine = sin(f->theta);
  f->cosine = cos(f->theta);
  f->i_d = f->i_alpha * f->cosine + f->i_beta * f->sine;
  f->i_q = f->i_beta * f->cosine - f->i_alpha * f->sine;
}

void Ipark(FOC* f){
  f->sine = sin(f->theta);
  f->cosine = cos(f->theta);
  f->u_alpha = f->u_d * f->cosine - f->u_q * f->sine;
  f->u_beta = f->u_q * f->cosine + f->u_d * f->sine;
}

void SVPWM(FOC* f){
    //iclarke
    // sqrt(3)/2 = 0.8660254037844386
    // float u2 = -0.8660254037844386 * u_alpha - u_beta / 2;
    // float u3 = 0.8660254037844386 * u_alpha - u_beta / 2;

    const ElementType ts = 1;
    ElementType u1 = f->u_beta;
    ElementType tmp1 = 0.8660254037844386f * f->u_alpha;
    ElementType tmp2 = f->u_beta / 2;
    ElementType u2 = -tmp1 - tmp2;
    ElementType u3 = tmp1 - tmp2;
    unsigned char sector = (u1>0.0f) | ((u2>0.0f) << 1) | ((u3>0.0f) << 2);

    if (sector == 5) {
        ElementType t4 = u3;
        ElementType t6 = u1;
        ElementType sum = t4 + t6;
        if (sum > ts) {
            f->k_svpwm = ts / sum;
            t4 = f->k_svpwm * t4;
            t6 = f->k_svpwm * t6;
        }
        ElementType t7 = (ts - t4 - t6) / 2;
        f->t_a = t4 + t6 + t7;
        f->t_b = t6 + t7;
        f->t_c = t7;
    } else if (sector == 1) {
        ElementType t2 = -u3;
        ElementType t6 = -u2;
        ElementType sum = t2 + t6;
        if (sum > ts) {
            f->k_svpwm = ts / sum;
            t2 = f->k_svpwm * t2;
            t6 = f->k_svpwm * t6;
        }
        ElementType t7 = (ts - t2 - t6) / 2;
        f->t_a = t6 + t7;
        f->t_b = t2 + t6 + t7;
        f->t_c = t7;
    } else if (sector == 3) {
        ElementType t2 = u1;
        ElementType t3 = u2;
        ElementType sum = t2 + t3;
        if (sum > ts) {
            f->k_svpwm = ts / sum;
            t2 = f->k_svpwm * t2;
            t3 = f->k_svpwm * t3;
        }
        ElementType t7 = (ts - t2 - t3) / 2;
        f->t_a = t7;
        f->t_b = t2 + t3 + t7;
        f->t_c = t3 + t7;
    } else if (sector == 2) {
        ElementType t1 = -u1;
        ElementType t3 = -u3;
        ElementType sum = t1 + t3;
        if (sum > ts) {
            f->k_svpwm = ts / sum;
            t1 = f->k_svpwm * t1;
            t3 = f->k_svpwm * t3;
        }
        ElementType t7 = (ts - t1 - t3) / 2;
        f->t_a = t7;
        f->t_b = t3 + t7;
        f->t_c = t1 + t3 + t7;
    } else if (sector == 6) {
        ElementType t1 = u2;
        ElementType t5 = u3;
        ElementType sum = t1 + t5;
        if (sum > ts) {
            f->k_svpwm = ts / sum;
            t1 = f->k_svpwm * t1;
            t5 = f->k_svpwm * t5;
        }
        ElementType t7 = (ts - t1 - t5) / 2;
        f->t_a = t5 + t7;
        f->t_b = t7;
        f->t_c = t1 + t5 + t7;
    } else if (sector == 4) {
        ElementType t4 = -u2;
        ElementType t5 = -u1;
        ElementType sum = t4 + t5;
        if (sum > ts) {
            f->k_svpwm = ts / sum;
            t4 = f->k_svpwm * t4;
            t5 = f->k_svpwm * t5;
        }
        ElementType t7 = (ts - t4 - t5) / 2;
        f->t_a = t4 + t5 + t7;
        f->t_b = t7;
        f->t_c = t5 + t7;
    }
}
