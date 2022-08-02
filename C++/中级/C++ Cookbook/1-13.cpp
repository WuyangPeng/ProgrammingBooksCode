# Jamfile for project hellobeatles
exe hellobeatles
   : # sources
      ../johnpaul//libjohnpaul
      ../georgeringo//libgeorgeringo
      hellobeatles.cpp
   ;
   install dist
   : # sources
      hellobeatles
   : # requirements
      <install-dependencies>on
      <install-type>EXE
      <install-type>SHARED_LIB
      <location>.
   ;
