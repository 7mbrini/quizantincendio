object FormDebug: TFormDebug
  Left = 0
  Top = 0
  Caption = 'Debug'
  ClientHeight = 366
  ClientWidth = 395
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  TextHeight = 13
  object Image: TImage
    Left = 0
    Top = 0
    Width = 395
    Height = 347
    Align = alClient
    ExplicitLeft = 142
    ExplicitTop = 164
    ExplicitWidth = 105
    ExplicitHeight = 105
  end
  object RichEdit: TRichEdit
    Left = 0
    Top = 0
    Width = 395
    Height = 347
    Align = alClient
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Verdana'
    Font.Style = [fsBold]
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 347
    Width = 395
    Height = 19
    Panels = <>
    ExplicitLeft = 102
    ExplicitTop = 296
    ExplicitWidth = 0
  end
  object MainMenu: TMainMenu
    Left = 209
    Top = 66
    object MenuFile: TMenuItem
      Caption = '&File'
      object FileSaveAs: TMenuItem
        Caption = '&Save As ...'
        OnClick = FileSaveAsClick
      end
    end
    object MenuActions: TMenuItem
      Caption = '&Actions'
      object ActionsClear: TMenuItem
        Caption = '&Clear'
        OnClick = ActionsClearClick
      end
      object OpMode1: TMenuItem
        Caption = '&OpMode'
        object ext1: TMenuItem
          Caption = '&Text'
          OnClick = ext1Click
        end
        object Images1: TMenuItem
          Caption = '&Image'
          OnClick = Images1Click
        end
      end
    end
  end
  object SaveDialog: TSaveDialog
    DefaultExt = '*.txt'
    Filter = 'Ascii text file|*.txt'
    Left = 287
    Top = 64
  end
end
