cmake_minimum_required(VERSION 2.8.0)
 project(SCHEMATIC)

 set (CMAKE_CXX_FLAGS            "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE)
 set (CMAKE_INSTALL_PREFIX       "../install" )

    find_package(LibXml2)
    include_directories( ${SCHEMATIC_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR}
                       )

                    set( includes     Indentation.h
                                      XmlUtil.h
                                      Term.h
                                      Net.h
                                      Instance.h
                                      Point.h
                                      Node.h
                                      Cell.h
                                      Line.h
                                      Box.h
                                      Shape.h
                                      Symbol.h


                       )

                    set( cpps         Indentation.cpp
                                      XmlUtil.cpp
                                      Term.cpp
                                      Net.cpp
                                      Instance.cpp
                                      Point.cpp
                                      Node.cpp
                                      Cell.cpp
                                      Main.cpp
                                      Line.cpp
                                      Box.cpp
                                      Shape.cpp
                                      Symbol.cpp
                       )

        add_executable ( tme7        ${cpps} )
        target_link_libraries ( tme7 ${LIBXML2_LIBRARIES} )
               install ( TARGETS      tme7        DESTINATION bin )
               install ( FILES        ${includes}  DESTINATION include )
