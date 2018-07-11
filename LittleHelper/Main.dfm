object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = []
  Caption = 'whatthefuck!'
  ClientHeight = 303
  ClientWidth = 415
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object TrayIcon1: TTrayIcon
    PopupMenu = PopupMenu1
    Visible = True
    Left = 552
    Top = 96
  end
  object PopupMenu1: TPopupMenu
    Left = 32
    object FuckOFF1: TMenuItem
      Caption = 'FuckOFF'
      OnClick = FuckOFF1Click
    end
    object Scanforshit1: TMenuItem
      Caption = 'Scan for shit'
    end
    object Options1: TMenuItem
      Caption = 'Options'
    end
  end
  object Timer1: TTimer
    Interval = 10
    OnTimer = Timer1Timer
  end
end
