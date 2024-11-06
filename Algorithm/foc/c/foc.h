#ifndef __FOC_H_
#define __FOC_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef float   ElementType;

typedef struct{
	ElementType u_alpha;
	ElementType u_beta;
	ElementType u_d;
	ElementType u_q;

	ElementType i_alpha;
	ElementType i_beta;
	ElementType i_d;
	ElementType i_q;
	ElementType theta;
	
	ElementType i_a;
	ElementType i_b;
	ElementType i_c;
	ElementType t_a;
	ElementType t_b;
	ElementType t_c;

	ElementType sine;
	ElementType cosine;
	ElementType k_svpwm;
}FOC;

void InitFOC(FOC* f);
void Clarke(FOC* f);
void Park(FOC* f);
void Ipark(FOC* f);
void SVPWM(FOC* f);

#ifdef __cplusplus
}
#endif

#endif /* __FOC_H_ */
