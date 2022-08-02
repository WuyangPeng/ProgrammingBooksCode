/*
 code that uses a single polynomial to implement  an ease-in/ease-out function
*/

float ease(float t)
{
  return (t*(3*t - 2*t*t));
}
