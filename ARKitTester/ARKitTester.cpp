#include "ARKitLib.h"

int main()
{
    ARKitLib obj;

    // Get process list
    {
        std::list<ARKPROCESS> procList;
        obj.getProcessList( procList );

        printf( "\n\nGot %d processes", procList.size() );
        std::list<ARKPROCESS>::iterator itProc = procList.begin();
        for( int i = 0; itProc != procList.end(); itProc++ )
        {
            ++i;
            printf( "\n%d] %s - %d", i, itProc->procName, itProc->procId );
        }
    }

    // Get driver list
    {
        std::list<ARKDRIVER> driverList;
        obj.getDriverList( driverList );

        printf( "\n\nGot %d drivers", driverList.size() );
        std::list<ARKDRIVER>::iterator itDrv = driverList.begin();
        for( int i = 0; itDrv != driverList.end(); itDrv++ )
        {
            ++i;
            printf( "\n%d] %s - 0x%x", i, itDrv->driverName, itDrv->baseAddr );
        }
    }

    // Get SSDT hooks list
    {
        std::list<ARKSSDTHOOK> ssdtHookList;
        obj.getSSDTHooksList( ssdtHookList );

        printf( "\n\nGot %d SSDT hooks", ssdtHookList.size() );
        std::list<ARKSSDTHOOK>::iterator itSsdtHook = ssdtHookList.begin();
        for( int i = 0; itSsdtHook != ssdtHookList.end(); itSsdtHook++ )
        {
            ++i;
            printf( "\n%d] %s - %s - 0x%x", i, itSsdtHook->driverName, itSsdtHook->ssdtFuncName, itSsdtHook->hookAddr );
        }
    }

    // Get DLLs loaded in current process
    {
        DWORD dwPid = 0;
        std::list<ARKDLL> dllList;
        printf( "\n\n\nEnter pid to get DLLs: " );
        scanf( "%d", &dwPid );
        obj.getDllList( dwPid, dllList );

        printf( "\n\nGot %d DLLs", dllList.size() );
        std::list<ARKDLL>::iterator itDlls = dllList.begin();
        for( int i = 0; itDlls != dllList.end(); itDlls++ )
        {
            ++i;
            printf( "\n%d] %s - 0x%x", i, itDlls->dllName, itDlls->baseAddr );
        }
    }

    // Get kernel inline hooks
    {
        std::list<ARKINLINEHOOK> inlineHookList;
        obj.getKernelInlineHooks( inlineHookList );

        printf( "\n\nGot %d inline hooks", inlineHookList.size() );
        std::list<ARKINLINEHOOK>::iterator itHooks = inlineHookList.begin();
        for( int i = 0; itHooks != inlineHookList.end(); itHooks++ )
        {
            ++i;
            printf( "\n%d] %s - %s - 0x%x", i, itHooks->funcName, itHooks->driverName, itHooks->jumpToAddr );
        }
    }

    // Kill a process
    {
        DWORD dwPid = 0;
        printf( "\n\n\nEnter pid to kill: " );
        scanf( "%d", &dwPid );
        if( obj.killProcess( dwPid ) )
        {
            printf( "\nProcess killed successfully!\n" );
        }
        else
        {
            printf( "\nFailed to kill process\n" );
        }
    }

    // Fix SSDT hook by index
    {
        UINT unSsdtIndex = 0;
        printf( "\n\n\nEnter SSDT index to fix: " );
        scanf( "%d", &unSsdtIndex );
        if( obj.fixSsdtHook( unSsdtIndex ) )
        {
            printf( "\nSSDT hook fixed successfully!\n" );
        }
        else
        {
            printf( "\nFailed to fix SSDT hook\n" );
        }
    }

    // Fix SSDT hook by name
    {
        char szZwFuncName[ARKITLIB_STR_LEN];
        ::ZeroMemory( szZwFuncName, ARKITLIB_STR_LEN );
        printf( "\n\n\nEnter SSDT ZwXxx function name to fix: " );
        scanf( "%s", szZwFuncName );

        std::string strZwFuncName( szZwFuncName );
        if( obj.fixSsdtHook( strZwFuncName ) )
        {
            printf( "\nSSDT hook fixed successfully!\n" );
        }
        else
        {
            printf( "\nFailed to fix SSDT hook\n" );
        }
    }

    // Fix inline hook by name
    {
        char szFuncName[ARKITLIB_STR_LEN];
        ::ZeroMemory( szFuncName, ARKITLIB_STR_LEN );
        printf( "\n\n\nEnter kernel function name to fix: " );
        scanf( "%s", szFuncName );

        std::string strFuncName( szFuncName );
        if( obj.fixInlineHook( strFuncName ) )
        {
            printf( "\nInline hook fixed successfully!\n" );
        }
        else
        {
            printf( "\nFailed to fix inline hook\n" );
        }
    }
    
    return 0;
}
