unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    btnOK: TButton;
    btnCancel: TButton;
    procedure btnOKClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.btnOKClick(Sender: TObject);
begin
  Application.MessageBox('Button <OK> pressed.', 'Information');
end;

procedure TForm1.btnCancelClick(Sender: TObject);
begin
  Application.MessageBox('Button <Cancel> pressed.', 'Information');
end;

end.
