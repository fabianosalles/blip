unit FormUtil;
{ form appearence and
other various utilities
(by Giulio Ferrari 1996) }

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

{ procedures for hiding/showing form's title bar }
procedure HideTitle(Sender: TForm);
procedure ShowTitle(Sender: TForm);
{ procedure that simulate Turbo Pascal's 'Delay' }
procedure Delay(msecs:integer);
{ function to convert integers to GB/MB/KB format }
function ByteConvert(Bytes: Cardinal): String;

implementation

procedure HideTitle(Sender: TForm);
var
  Save : LongInt;
Begin
with (sender as TForm) do begin
  If BorderStyle=bsNone then Exit;
  Save:=GetWindowLong(Handle,gwl_Style);
  If (Save and ws_Caption)=ws_Caption then Begin
    Case BorderStyle of
      bsSingle,
      bsSizeable : SetWindowLong(Handle,gwl_Style,Save and
        (Not(ws_Caption)) or ws_border);
      bsDialog : SetWindowLong(Handle,gwl_Style,Save and
        (Not(ws_Caption)) or ds_modalframe or ws_dlgframe);
    End;
    Height:=Height-getSystemMetrics(sm_cyCaption);
    Refresh;
  End;
  end;
end;

procedure ShowTitle(Sender: TForm);
var
  Save : LongInt;
begin
with (sender as TForm) do begin
  If BorderStyle=bsNone then Exit;
  Save:=GetWindowLong(Handle,gwl_Style);
  If (Save and ws_Caption)<>ws_Caption then Begin
    Case BorderStyle of
      bsSingle,
      bsSizeable : SetWindowLong(Handle,gwl_Style,Save or ws_Caption or
        ws_border);
      bsDialog : SetWindowLong(Handle,gwl_Style,Save or ws_Caption or
        ds_modalframe or ws_dlgframe);
    End;
    Height:=Height+getSystemMetrics(sm_cyCaption);
    Refresh;
  End;
end;
end;

procedure Delay(msecs:integer);
var
 firstTickCount:longint;
begin
 firstTickCount:=getTickCount;
 repeat
 application.processMessages;
 until ((getTickCount-firstTickCount) >= longint(msecs));
end;

function ByteConvert(Bytes: Cardinal): String;
begin
if Bytes >= 1073741824 then
Result := IntToStr(Bytes div 1073741824)
+','+IntToStr(Trunc((Bytes mod 1073741824)/107374182))+' GB'
else if Bytes >= 1048576 then
Result := IntToStr(Bytes div 1048576)
+','+IntToStr(Trunc((Bytes mod 1048576)/104857))+' MB'
else if Bytes >= 1024 then
Result := IntToStr(Bytes div 1024)
+','+IntToStr(Trunc((Bytes mod 1024)/102))+' KB'
else Result := IntToStr(Bytes)+'  B';
end;

end.
