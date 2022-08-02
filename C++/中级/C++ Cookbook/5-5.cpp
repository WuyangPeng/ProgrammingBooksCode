using boost::gregorian;
using boost::posix_time;

void dateToTmAux(const date& src, tm& dest) {
  dest.tm_mday = src.day( );
  dest.tm_year = src.year( ) - 1900;
  dest.tm_mon = src.month( ) - 1;
}

void ptimeToTmAux(const ptime& src, tm& dest) {
  dest.tm_sec = src.seconds( );
  dest.tm_min = src.minutes( );
  dest.tm_hour = src.hours( );
  dateToTmAux(src.date( ), dest);
}

tm ptimeToTm(const ptime& t) {
  tm ret = tm( ); 
  ptimeToTmAux(t, ret);
  return ret;
}
