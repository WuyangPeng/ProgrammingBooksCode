# Jamfile for project libjohnpaul
   lib libjohnpaul
   : # sources
      john.cpp paul.cpp johnpaul.cpp
   : # requirements
      <link>static
   : # default-build
   : # usage-requirements
      <include>..
   ;
