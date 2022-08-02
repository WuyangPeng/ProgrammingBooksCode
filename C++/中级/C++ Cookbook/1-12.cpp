# Jamfile for project georgringo
lib libgeorgeringo
   : # sources
      george.cpp ringo.cpp georgeringo.cpp
   : # requirements
      <link>shared
      <define>GEORGERINGO_DLL
   : # default-build
   : # usage-requirements
      <include>..
   ;
