install(DIRECTORY "${SGE_DIR}/Action"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/IO"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Level"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Logic"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Object"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Game"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Renderer"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Scene"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/PicoPNG"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Box2D"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Utils"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")