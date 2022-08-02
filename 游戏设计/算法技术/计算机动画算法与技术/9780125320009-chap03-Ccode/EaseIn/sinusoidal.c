/*
 code that uses sinusoidal end segments  and an interior linear segment to piece together an ease-in/ease-out function
*/

float ease(float t, float k1, float k2){  float t1,t2;  float f; f = k1*2/PI + k2 - k1 + (1.0-k2)*2/PI;  if (t<k1) {  s = (sin((t/k1)*PI/2-PI/2)+1)/f; }  else if (t < k2) {    s = (2*k1/PI + t-k1)/f; }  else {   s= 2*k1/PI + k2-k1 + sin(((t-k2)/(1.0-k2))*PI/2)/f; }  return s;}