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
                                      LineShape.h
                                      BoxShape.h
                                      EllipseShape.h
                                      ArcShape.h
                                      TermShape.h
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
                                      LineShape.cpp
                                      BoxShape.cpp
                                      EllipseShape.cpp
                                      ArcShape.cpp
                                      TermShape.cpp
                                      Symbol.cpp
                       )

        add_executable ( tme6        ${cpps} )
        target_link_libraries ( tme6 ${LIBXML2_LIBRARIES} )
               install ( TARGETS      tme6        DESTINATION bin )
               install ( FILES        ${includes}  DESTINATION include )
