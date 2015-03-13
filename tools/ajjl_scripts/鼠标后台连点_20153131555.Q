[General]
SyntaxVersion=2
BeginHotkey=120
BeginHotkeyMod=0
PauseHotkey=0
PauseHotkeyMod=0
StopHotkey=123
StopHotkeyMod=0
RunOnce=1
EnableWindow=
MacroID=4b845359-bcf9-4534-a080-ed287e5ef17f
Description=鼠标后台连点
Enable=1
AutoRun=0
[Repeat]
Type=0
Number=1
[SetupUI]
Type=2
QUI=
[Relative]
SetupOCXFile=
[Comment]

[Script]
Dim hFgWin, wp

hFgWin = Plugin.Window.Foreground()

If hFgWin = 0 Then 
	Call MessageBox("当前无前置窗口")
	ExitScript
End If

wp = getMousePointForWindow(hFgWin)

Do
Call Plugin.Bkgnd.LeftClick(hFgWin, wp(0), wp(1))
Delay 100
Loop


Function getMousePointForWindow(hWin)

Dim wRect, wArray, mArray, mX, mY, wpArr(2)

wRect = Plugin.Window.GetClientRect(hWin)
wArray = Split(wRect, "|")
GetCursorPos mX, mY
wpArr(0) = mX - wArray(0)
wpArr(1) = mY - wArray(1)
getMousePointForWindow = wpArr

End Function