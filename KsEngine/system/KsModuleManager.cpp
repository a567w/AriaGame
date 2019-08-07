#if 0

KsModuleManager::KsModuleManager()
{
}


KsModuleManager::~KsModuleManager()
{
	vector< Module* > vpkModules;

	m_hashModules.GetAllNodeData( &vpkModules );

	vector< Module* >::iterator ppkModule    = vpkModules.begin();
	vector< Module* >::iterator ppkModuleEnd = vpkModules.end();

	for( ; ppkModule != ppkModuleEnd; ++ppkModule )
	{
		if( ( (*ppkModule)->GetRefCount() > 0 ) && !(*ppkModule)->IsStatic() )
		{
			//If you hit this assert, module was not unloaded/deregistered correctly
			assert( false );

			neolog << LogLevel( WARNING ) << "[KsModuleManager::~KsModuleManager]: Module [" << (*ppkModule)->GetName() << "] not unloaded correctly" << endl;

			delete( *ppkModule );
		}
		else
			RemoveModule( *ppkModule );
	}
}


KsBool KsModuleManager::addSearchPath( const KsString& path )
{	
	m_searchPaths.push_back( path );


	KsUInt32		length = path.length()
	KsInt32		idx;
	KsString		newPath;
	KsChar*			pData = path.c_str();

	for( idx=0; idx<length; ++idx )
	{
		if( pData[ idx ] == '\\' )
		{
			newPath += '/';
		}
		else
		{
			newPath += pData[ idx ];
		}
	}

	if( !idx || ( newPath.m_strData[ idx - 1 ] != '/' ) )
		strNewPath.m_strData += '/';


	if( !idx || ( strNewPath.m_strData[ idx - 1 ] != '/' ) )
		strNewPath.m_strData += '/';

	strNewPath.HashMe();

	vector< HashString >::iterator pstrPath    = m_vstrSearchPaths.begin();
	vector< HashString >::iterator pstrPathEnd = m_vstrSearchPaths.end();

	for( ; pstrPath != pstrPathEnd; ++pstrPath )
	{
		if( *pstrPath == strNewPath )
		{
			// The directory is already in our search path
			return false;
		}
	}

	if( !PathExists( strNewPath ) && ( bForce == false ) )
	{
		neolog << LogLevel( INFO ) << "[KsModuleManager::AddSearchPath]: The path [" << strNewPath << "] does not exist" << endl;

		return false;
	}
	else
	{
		m_vstrSearchPaths.push_back( strNewPath );
		neolog << LogLevel( INFO ) << "[KsModuleManager::AddSearchPath]: Added [" << strNewPath << "] to search path" << endl;

		return true;
	}
}


void KsModuleManager::removeSearchPath( const KsString& path )
{
	unsigned int uiPos;
	HashString strNewPath;

	for( uiPos = 0; uiPos < rstrPath.length(); ++uiPos )
	{
		if( rstrPath.m_strData[ uiPos ] == '\\' )
			strNewPath.m_strData += '/';
		else
			strNewPath.m_strData += rstrPath.m_strData[ uiPos ];
	}

	if( !uiPos || ( strNewPath.m_strData[ uiPos - 1 ] != '/' ) )
		strNewPath.m_strData += '/';

	strNewPath.HashMe();

	vector< HashString >::iterator pstrPath    = m_vstrSearchPaths.begin();
	vector< HashString >::iterator pstrPathEnd = m_vstrSearchPaths.end();

	for( ; pstrPath != pstrPathEnd; ++pstrPath )
	{
		if( *pstrPath == strNewPath )
		{
			// The directory is already in our search path
			m_vstrSearchPaths.erase( pstrPath );
			return;
		}
	}
}





void* KsModuleManager::loadModule( const KsString& name )
{
	ModulePtr  pkMod;
	void*		pModuleAddress;
	FILE*		pFile;

	if( ( pModuleAddress = m_hashModules.find( name ) ) )
	{
		return pModuleAddress;
	}

	KsString strFilename = rstrName.m_strData + ".dll";
	KsString strModulePath;

	vector< HashString >::iterator pstrPath    = m_vstrSearchPaths.begin();
	vector< HashString >::iterator pstrPathEnd = m_vstrSearchPaths.end();

	for( ; pstrPath != pstrPathEnd; ++pstrPath )
	{
		strModulePath = pstrPath->m_strData + strFilename;

		/* Check to see if the file exists at this path */
		pFile = fopen( strModulePath.c_str(), "r" );

		if( pFile )
		{
			fclose( pFile );

			if( ( pkMod = new ModuleDynamic( rstrName, strModulePath, this ) )->IsValid() )
			{
				InsertModule( pkMod );
					pkModule->m_pkManager = this;

	m_hashModules.Insert( pkModule->GetName(), pkModule );

				return pkMod;
			}

			pkMod = 0;
		}
	}

	// On MacOS X, consider the module to be part of the NeoEngine core bundle, so pass true.
	// This doesn't mean anything on any other platform, so they'll just disregard it.
	if( ( pkMod = new ModuleDynamic( rstrName, strFilename, this, true ) )->IsValid() )
		InsertModule( pkMod );
	else
		pkMod = 0;

	return pkMod;
}


void KsModuleManager::addModule( KsModule* pModule )
{
	if( !pModule )
	{
		return;
	}

	pModule->m_pManager = this;

	m_hashModules.add( pModule->getName(), pModule );
}


void KsModuleManager::removeModule( KsModule* pModule )
{
	if( !pModule )
	{
		return;
	}

}

	KsGlobalObject*		pObject = (KsGlobalObject*)KsGetHandleObject( handle );

	--pObject->m_refCount;
	if( pObject->m_refCount == 0 )
	{
		/* 構造体だったら開放する必要がある */
		if( pObject->getVariable()->getType() == ksVALUE_STRCT ){
			KsVariable*		pVariables = (KsVariable*)pObject->getVariable()->m_value.h;
			delete [] pVariables;
		}

		m_globalHandleList.destroy( pObject->getString().c_str() );
		delete pObject;
	}


KsBool KsModuleManager::isPathExists( const KsString& path )
{
	WIN32_FIND_DATA		wfData;
	KsChar				szPath[ ksPATH_MAX ];

	sprintf( szPath, "%s/*", path.c_str() );

	HANDLE	hFind = FindFirstFile( szPath, &wfData );

	if( hFind != INVALID_HANDLE_VALUE )
	{
		if( wfData.cFileName[0] != '.' )
		{
			if( wfData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				return ksTRUE;
			}
			else
			{
				return ksFALSE;
			}
		}
		else
		{
			return ksTRUE;
		}
	}
	else
	{
		return ksFALSE;
	}

	return ksFALSE;
}

#endif