#ifndef __SENS_H__
#define __SENS_H__



#ifdef __cplusplus 
extern "C" {
#endif
  
char data1[] = {'A','B','C'};
char data_i1[] = {'C','B','A'};
char data2[] = {'A','B','D','C'};
char data_i2[] = {'C','B','A'};
char data_i3[] = {'C','E','A'};

clock_t t1d[30], t2d[30],t3d[30];
clock_t t1a[30], t2a[30],t3a[30];

  extern void sens   (const char *);
  extern void sensInverse  (const char *);
   extern void Train1   (const char *);
  extern void Train2   (const char *);
  extern void Train3   (const char *);

#ifdef __cplusplus
} // extern C
#endif

#endif
