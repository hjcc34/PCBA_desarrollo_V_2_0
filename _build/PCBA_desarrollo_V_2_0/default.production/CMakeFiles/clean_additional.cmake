# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\production\\default-production.cmf"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\production\\default-production.hex"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\production\\default-production.hxl"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\production\\default-production.mum"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\production\\default-production.o"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\production\\default-production.sdb"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\production\\default-production.sym"
  )
endif()
