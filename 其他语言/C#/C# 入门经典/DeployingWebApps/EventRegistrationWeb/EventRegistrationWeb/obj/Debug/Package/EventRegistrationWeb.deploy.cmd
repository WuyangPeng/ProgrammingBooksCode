@rem ---------------------------------------------------------------------------------
@rem Copyright 2008 Microsoft Corporation. All rights reserved.
@rem This is provided as sample to deploy the package using msdeploy.exe
@rem For information about IIS MSDeploy technology,
@rem please visit http://go.microsoft.com/?linkid=9278654
@rem Note: This batch file assumes the package and setparametsrs.xml are in the same folder with this file
@rem ---------------------------------------------------------------------------------
@if %_echo%!==! echo off
setlocal
@rem ---------------------------------------------------------------------------------
@rem Please Make sure you have Msdeploy install in your machine. 
@rem Alternatively, you can explicit set the MsDeployPath to the location it is on your machine
@rem set MSDeployPath="C:\Program Files (x86)\IIS\Microsoft Web Deploy\"
@rem ---------------------------------------------------------------------------------
                      
@rem ---------------------------------------------------------------------------------
@rem if user does not set MsDeployPath environment variable, we will try to retrieve it from registry.
@rem ---------------------------------------------------------------------------------
if "%MSDeployPath%" == "" (
for /F "usebackq tokens=2*" %%i  in (`reg query "HKLM\SOFTWARE\Microsoft\IIS Extensions\MSDeploy\1" /v InstallPath`) do (
if "%%~dpj" == "%%j" ( 
set MSDeployPath=%%j
)))

if not exist "%MSDeployPath%\msdeploy.exe" (
echo. msdeploy.exe is not found on this machine. Please install msdeploy before execute the script. 
echo. Please visit http://go.microsoft.com/?linkid=9278654
goto :usage
)

set RootPath=%~dp0

set _ArgTestDeploy=
set _ArgDestinationType=auto
set _ArgComputerName=
set _ArgUserName=
set _ArgPassword=
set _ArgEncryptPassword=
set _ArgIncludeAcls=False
set _ArgAuthType=
set _ArgtempAgent=

@rem ---------------------------------------------------------------------------------
@rem Simple Parse the arguments
@rem ---------------------------------------------------------------------------------
:NextArgument
set _ArgCurrent=%~1

if /I "%_ArgCurrent%" == "" goto :GetStarted
if /I "%_ArgCurrent%" == "/T" set _ArgTestDeploy=true&goto :ArgumentOK
if /I "%_ArgCurrent%" == "/Y" set _ArgTestDeploy=false&goto :ArgumentOK

set _ArgFlag=%_ArgCurrent:~0,3%
set _ArgValue=%_ArgCurrent:~3%

if /I "%_ArgFlag%" == "/M:" set _ArgComputerName=%_ArgValue%&goto :ArgumentOK
if /I "%_ArgFlag%" == "/U:" set _ArgUserName=%_ArgValue%&goto :ArgumentOK
if /I "%_ArgFlag%" == "/P:" set _ArgUserPassword=%_ArgValue%&goto :ArgumentOK
if /I "%_ArgFlag%" == "/E:" set _ArgUserEncryptPassword=%_ArgValue%&goto :ArgumentOK
if /I "%_ArgFlag%" == "/I:" set _ArgIncludeAcls=%_ArgValue%&goto :ArgumentOK
if /I "%_ArgFlag%" == "/A:" set _ArgAuthType=%_ArgValue%&goto :ArgumentOK
if /I "%_ArgFlag%" == "/G:" set _ArgtempAgent=%_ArgValue%&goto :ArgumentOK

@rem Any additon flags, pass through to the msdeploy
set _ArgMsDeployAdditionalFlags=%_ArgMsDeployAdditionalFlags% %_ArgCurrent%

:ArgumentOK
shift
goto :NextArgument

:GetStarted
if /I "%_ArgTestDeploy%" == "" goto :usage
if /I "%_ArgDestinationType%" == ""  goto :usage

set _Destination=%_ArgDestinationType%
if not "%_ArgComputerName%" == "" set _Destination=%_Destination%,computerName='%_ArgComputerName%'
if not "%_ArgUserName%" == "" set _Destination=%_Destination%,userName='%_ArgUserName%'
if not "%_Argpassword%" == "" set _Destination=%_Destination%,password='%_ArgPassword%'
if not "%_ArgAuthType%" == "" set _Destination=%_Destination%,authtype='%_ArgAuthType%'
if not "%_ArgEncryptPassword%" == "" set _Destination=%_Destination%,encryptPassword='%_ArgEncryptPassword%'
if not "%_ArgIncludeAcls%" == "" set _Destination=%_Destination%,includeAcls='%_ArgIncludeAcls%'
if not "%_ArgtempAgent%" == "" set _Destination=%_Destination%,tempAgent='%_ArgtempAgent%'

@rem ---------------------------------------------------------------------------------
@rem add -whatif when -T is specified                      
@rem ---------------------------------------------------------------------------------
if /I "%_ArgTestDeploy%" NEQ "false" (
set _MsDeployAdditionalFlags=%_MsDeployAdditionalFlags% -whatif
)

@rem ---------------------------------------------------------------------------------
@rem pass through the addition MsDeploy Flags
@rem ---------------------------------------------------------------------------------
set _MsDeployAdditionalFlags=%_MsDeployAdditionalFlags% %_ArgMsDeployAdditionalFlags%

@rem ---------------------------------------------------------------------------------
@rem check the existance of the package file
@rem ---------------------------------------------------------------------------------
if not exist "%RootPath%EventRegistrationWeb.zip" (
echo "%RootPath%EventRegistrationWeb.zip" does not exist. 
echo This batch file relies on this deploy source file^(s^) in the same folder.
goto :usage
)

@rem ---------------------------------------------------------------------------------
@rem Execute Msdeploy command line
@rem ---------------------------------------------------------------------------------
call :CheckParameterFile
echo. Start executing msdeploy.exe
echo -------------------------------------------------------
if  not exist "%RootPath%EventRegistrationWeb.SetParameters.xml" (
echo. "%MSDeployPath%\msdeploy.exe" -source:package='%RootPath%EventRegistrationWeb.zip' -dest:%_Destination% -verb:sync -disableLink:AppPoolExtension -disableLink:ContentExtension -disableLink:CertificateExtension
"%MSDeployPath%\msdeploy.exe" -source:package='%RootPath%EventRegistrationWeb.zip' -dest:%_Destination% -verb:sync -disableLink:AppPoolExtension -disableLink:ContentExtension -disableLink:CertificateExtension
) else (
echo. "%MSDeployPath%\msdeploy.exe" -source:package='%RootPath%EventRegistrationWeb.zip' -dest:%_Destination% -verb:sync -disableLink:AppPoolExtension -disableLink:ContentExtension -disableLink:CertificateExtension -setParamFile:"%RootPath%EventRegistrationWeb.SetParameters.xml"
"%MSDeployPath%\msdeploy.exe" -source:package='%RootPath%EventRegistrationWeb.zip' -dest:%_Destination% -verb:sync -disableLink:AppPoolExtension -disableLink:ContentExtension -disableLink:CertificateExtension -setParamFile:"%RootPath%EventRegistrationWeb.SetParameters.xml"
)
goto :eof

@rem ---------------------------------------------------------------------------------
@rem Usage
@rem ---------------------------------------------------------------------------------
:usage
echo =========================================================
echo Usage:%~nx0 [/T^|/Y] [/D:DestinationType] [/M:ComputerName] [/U:userName] [/P:password] [/E:encryptPassword] [/I:includeAcls] [/G:tempAgent] [additional msdeploy flags ...]
echo Required flags:
echo /T  This will call msdeploy.exe with -whatif flag. (simulation)
echo /Y  This will call msdeploy.exe to deploy the package to the location
echo Optional flags:
echo /M:  Msdeploy destination ComputerName or Url Service. Default is local.
echo /U:  Msdeploy destination user name. 
echo /P:  Msdeploy destination password.
echo /E:  Msdeploy destination encryptPassword.
echo /I:  Msdeploy destination includeAcls. True or False(default).
echo /G:  Msdeploy destination tempAgent. True or False(default).
echo.[additional msdeploy flags]: note: " is required for passing = through command line.
echo  "-skip:objectName=setAcl" "-skip:objectName=dbFullSql"
echo.Alternative environment variable _MsDeployAdditionalFlags is also honored.
echo.
echo Please make sure MSDeploy is installed in the box.
echo.
echo In addition, you can change IIS Application Name, Physical path, 
echo connectionString and other deploy parameters in the following file:
echo "%RootPath%EventRegistrationWeb.SetParameters.xml"
echo =========================================================
goto :eof

@rem ---------------------------------------------------------------------------------
@rem CheckParameterFile -- check if the package's setparamters.xml exists or not
@rem ---------------------------------------------------------------------------------
:CheckParameterFile
echo =========================================================
if  exist "%RootPath%EventRegistrationWeb.SetParameters.xml" (
echo SetParameters from:
echo "%RootPath%EventRegistrationWeb.SetParameters.xml"
echo You can change IIS Application Name, Physical path, connectionString
echo or other deploy parameters in the above file.
) else (
echo SetParamterFiles does not exist in package location.
echo Use package embedded defaultValue to deploy.
)
echo -------------------------------------------------------
goto :eof
