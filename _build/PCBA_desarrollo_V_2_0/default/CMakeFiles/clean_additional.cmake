# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\default.cmf"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\default.hex"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\default.hxl"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\default.mum"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\default.o"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\default.sdb"
  "E:\\Mis Proyectos\\PCBA_desarrollo_V_2_0\\PCBA_desarrollo_V_2_0\\out\\PCBA_desarrollo_V_2_0\\default.sym"
  )
endif()
