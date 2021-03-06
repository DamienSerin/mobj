cmake_minimum_required(VERSION 2.8.0)
 project(SCHEMATIC)

 set (CMAKE_CXX_FLAGS            "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE)
 set (CMAKE_INSTALL_PREFIX       "../install" )

    find_package(LibXml2    REQUIRED)
    find_package(Qt4        REQUIRED)
    include(${QT_USE_FILE})
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
                    set( mocIncludes
                                      SaveCellDialog.h
                                      OpenCellDialog.h
                                      CellWidget.h
                                      CellViewer.h
                                      InstancesModel.h
                                      InstancesWidget.h
                                      CellsLib.h
                                      CellsModel.h

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
                				      SaveCellDialog.cpp
                                      OpenCellDialog.cpp
                				      CellWidget.cpp
                				      CellViewer.cpp
                                      InstancesModel.cpp
                                      InstancesWidget.cpp
                                      CellsLib.cpp
                                      CellsModel.cpp
                       )

        qt4_wrap_cpp(mocCpps    ${mocIncludes})

        add_executable ( tme810        ${cpps} ${mocCpps} )
        target_link_libraries ( tme810 ${QT_LIBRARIES} ${LIBXML2_LIBRARIES} )
               install ( TARGETS      tme810        DESTINATION bin )
               install ( FILES        ${includes} ${mocIncludes}  DESTINATION include )
