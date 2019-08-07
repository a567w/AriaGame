
#if 0
class KsSystemInfoGL
{
public:
	std::string			m_version;		/**< OpenGLのバージョン		*/
	std::string			m_extensions;	/**< OpenGLの拡張情報		*/
};

class KsSystemInfoGL::initialize()
{
	/* 使用するのOpenGLバージョンを取得する */
	m_version    = (KsChar*)glGetString( GL_VERSION );
	m_extensions = (KsChar*)glGetString( GL_EXTENSIONS );


	        // Set extension list
		std::stringstream ext;
        String str;

        const GLubyte* pcExt = glGetString(GL_EXTENSIONS);
        LogManager::getSingleton().logMessage("GL_EXTENSIONS = " + String((const char*)pcExt));

        assert(pcExt && "Problems getting GL extension string using glGetString");

        ext << pcExt;

        while(ext >> str)
        {
            extensionList.insert(str);
        }

        ext.str("");


	"GL_ARB_multitexture"

	s32 len = (s32)strlen((const char*)t);
	c8 *str = new c8[len+1];
	c8* p = str;

	for (s32 i=0; i<len; ++i)
	{
		str[i] = (char)t[i];

		if (str[i] == ' ')
		{
			str[i] = 0;
			if (strstr(p, "GL_ARB_multitexture"))
			{
				MultiTextureExtension = true;
				break;
			}

			p = p + strlen(p) + 1;
		}
	}

		if (MultiTextureExtension)
	{
		#ifdef _WIN32
		// get function pointers
		glActiveTextureARB   = (PFNGLACTIVETEXTUREARBPROC) wglGetProcAddress("glActiveTextureARB");
		glClientActiveTextureARB= (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTextureARB");
		if (!glActiveTextureARB || !glClientActiveTextureARB)
		{
			MultiTextureExtension = false;
			os::Printer::log("Failed to load OpenGL's multitexture extension, proceeding without.", ELL_WARNING);
		}
		#else
		MultiTextureExtension = false;
		os::Printer::log("Multitexturing disabled.", ELL_WARNING);
		#endif

		glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &MaxTextureUnits);
	}

	if (MaxTextureUnits < 2)
	{
		MultiTextureExtension = false;
		os::Printer::log("Warning: OpenGL device only has one texture unit. Disabling multitexturing.", ELL_WARNING);
	}
}

#endif