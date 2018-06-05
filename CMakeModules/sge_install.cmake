
install(DIRECTORY "${SGE_DIR}/IO"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Sprite"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Shape"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Renderer"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Renderer"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.frag")
install(DIRECTORY "${SGE_DIR}/Renderer"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.vert")
install(DIRECTORY "${SGE_DIR}/PicoPNG"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Camera2d"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")
install(DIRECTORY "${SGE_DIR}/Utils"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING
        PATTERN "*.h*")