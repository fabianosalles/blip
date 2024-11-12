unit myabout;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, StdCtrls,
  Buttons, ExtCtrls, FormUtil;

type
  TAboutBox = class(TForm)
    OKButton: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Panel1: TPanel;
    Timer1: TTimer;
    Label8: TLabel;
    Bevel2: TBevel;
    procedure OKButtonClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  AboutBox: TAboutBox;

implementation

{$R *.DFM}

procedure TAboutBox.OKButtonClick(Sender: TObject);
begin
close;
end;

procedure TAboutBox.FormCreate(Sender: TObject);
begin
if intToStr(diskfree(0))<>'-1' then
label6.caption:='Free Disk Space: '+byteConvert(diskfree(0));
end;

procedure TAboutBox.Timer1Timer(Sender: TObject);
begin
label7.caption := 'Current Time: ' + TimeToStr(Time);
end;

end.

