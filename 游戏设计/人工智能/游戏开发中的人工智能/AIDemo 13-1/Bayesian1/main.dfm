object Form1: TForm1
  Left = 288
  Top = 110
  Width = 362
  Height = 640
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 104
    Top = 352
    Width = 50
    Height = 13
    Caption = 'Prediction:'
  end
  object Label3: TLabel
    Left = 104
    Top = 328
    Width = 10
    Height = 13
    Caption = 'B:'
  end
  object Label4: TLabel
    Left = 104
    Top = 304
    Width = 10
    Height = 13
    Caption = 'A:'
  end
  object Label5: TLabel
    Left = 168
    Top = 328
    Width = 7
    Height = 13
    Caption = 'B'
  end
  object Label6: TLabel
    Left = 168
    Top = 304
    Width = 7
    Height = 13
    Caption = 'A'
  end
  object Label8: TLabel
    Left = 168
    Top = 352
    Width = 32
    Height = 13
    Caption = 'Label8'
  end
  object Label2: TLabel
    Left = 104
    Top = 376
    Width = 43
    Height = 13
    Caption = 'Random:'
  end
  object Label7: TLabel
    Left = 168
    Top = 376
    Width = 32
    Height = 13
    Caption = 'Label7'
  end
  object Label9: TLabel
    Left = 256
    Top = 352
    Width = 32
    Height = 13
    Caption = 'Label9'
  end
  object Label10: TLabel
    Left = 256
    Top = 376
    Width = 38
    Height = 13
    Caption = 'Label10'
  end
  object StringGrid1: TStringGrid
    Left = 8
    Top = 8
    Width = 337
    Height = 265
    FixedCols = 0
    RowCount = 10
    TabOrder = 0
  end
  object Button1: TButton
    Left = 8
    Top = 280
    Width = 75
    Height = 25
    Caption = 'P'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 312
    Width = 75
    Height = 25
    Caption = 'LK'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 8
    Top = 344
    Width = 75
    Height = 25
    Caption = 'HK'
    TabOrder = 3
    OnClick = Button3Click
  end
end
