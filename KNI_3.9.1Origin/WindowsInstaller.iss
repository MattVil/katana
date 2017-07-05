#define KNIVERSION "3.9.0"; define constant
#define KNIRELEASE ""; define constant
[Setup]
ShowLanguageDialog=auto
VersionInfoVersion={#KNIVERSION}
VersionInfoCompany=Neuronics AG
VersionInfoDescription=Katana Native Interface
VersionInfoCopyright=Switzerland 2007, Neuronics AG
AppCopyright=Neuronics AG
AppName=KatanaNativeInterface
AppVerName=Katana Native Interface v{#KNIVERSION}{#KNIRELEASE}
LicenseFile=LICENSE.txt
PrivilegesRequired=admin
DefaultDirName={pf}\Neuronics AG\KatanaNativeInterface
AppID={{6096C108-7512-489E-AA7C-6379BBF22E14}
AppPublisher=Neuronics AG
AppPublisherURL=http://www.neuronics.ch
AppSupportURL=http://www.neuronics.ch
AppUpdatesURL=http://www.neuronics.ch
DisableProgramGroupPage=false
OutputDir=.
OutputBaseFilename=KatanaNativeInterface-v{#KNIVERSION}{#KNIRELEASE}
DefaultGroupName=Katana Native Interface
[Files]
Source: lib\win32\*.lib; DestDir: {app}\lib\win32; Flags: overwritereadonly; Components: Libraries
Source: configfiles300\*; DestDir: {app}\configfiles300; Flags: confirmoverwrite; Components: Libraries
Source: configfiles400\*; DestDir: {app}\configfiles400; Flags: confirmoverwrite; Components: Libraries
Source: doc\KNI Manual.pdf; DestDir: {app}\doc; Flags: overwritereadonly; Components: Documentation
Source: include\*; DestDir: {app}\include; Flags: recursesubdirs; Excludes: *~; Components: Libraries
Source: py\KNI.py; DestDir: {code:GetPythonDir}\Lib\site-packages; Components: PythonBindings
Source: py\KNIWrapper.py; DestDir: {code:GetPythonDir}\Lib\site-packages; Components: PythonBindings
Source: py\*.i; DestDir: {app}\py\swig; Components: PythonBindings
Source: demo\*; DestDir: {app}\demo; Flags: recursesubdirs; Components: Demos; Excludes: Makefile*, Release, Debug, *.pdb, *.user, *.exp, *.orig, *.idb, *.manifest, *.htm
Source: KNI.net\*; DestDir: {app}\KNI.net; Components: KNInet
Source: py\demo\*.py; DestDir: {app}\py\demo; Components: PythonBindings
Source: src\*; DestDir: {app}\src; Flags: recursesubdirs; Components: Sourcecode; Excludes: *~
Source: *.txt; DestDir: {app}; Components: Libraries
Source: KatanaNativeInterface.sln; DestDir: {app}; Components: Libraries
Source: KatanaNativeInterface.suo; DestDir: {app}; Components: Libraries

[Components]
Name: Libraries; Description: The KNI libraries (DLL and LIB); Flags: fixed; Types: custom compact full
Name: Demos; Description: Demo Applications; Types: full
Name: KNInet; Description: KNI .net binding; Types: full
Name: Documentation; Description: Documentation (Contains the KNI Manual and the API Reference); Types: full
Name: PythonBindings; Description: Bindings for Python
Name: PythonBindings\Python22; Description: Python v2.2; Flags: exclusive
Name: PythonBindings\Python23; Description: Python v2.3; Flags: exclusive
Name: PythonBindings\Python24; Description: Python v2.4; Flags: exclusive
Name: Sourcecode; Description: The KNI source code; Types: full

[Code]
var
	PythonBindingsDir: TInputDirWizardPage;

procedure InitializeWizard;
begin
	{ Create the pages }

	PythonBindingsDir := CreateInputDirPage(wpSelectComponents,
		'Select Python Directory', 'Where is Python installed?',
		'Please select the Python installation folder.',
		False, '');
	PythonBindingsDir.Add('');
	PythonBindingsDir.Values[0] := GetPreviousData('DataDir', '');;
end;

function ShouldSkipPage(PageID: Integer): Boolean;
begin
	{ Skip pages that shouldn't be shown }
	if (PageID = PythonBindingsDir.ID) then begin
		if IsComponentSelected('PythonBindings') then begin
			Result := False
		end else begin
			Result := True;
		end;
	end else begin
		Result := False;
	end;
end;

function GetPythonDir(get:String): String;
begin
	Result:=PythonBindingsDir.Values[0];
end;
[Icons]
Name: {group}\KNI Manual; Filename: {app}\doc\KNI Manual.pdf; Comment: Katana Native Interface Manual; Components: Documentation
Name: {group}\API Reference; Filename: {app}\doc\html\index.html; Comment: KNI API Reference; Components: Documentation
Name: {group}\Demo Applications; Filename: {app}\demo; Components: Demos
Name: {group}\KNI Visual C++ Solution; Filename: {app}\KatanaNativeInterface.sln; Components: Demos
Name: {group}\Uninstall; Filename: {uninstallexe}
[_ISToolPreCompile]
Name: doxygen.exe; Parameters: Doxyfile.conf
