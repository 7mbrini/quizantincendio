object FormDBSearch: TFormDBSearch
  Left = 0
  Top = 0
  Caption = 'Search by Keywords'
  ClientHeight = 444
  ClientWidth = 766
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poDesigned
  OnCanResize = FormCanResize
  OnCreate = FormCreate
  TextHeight = 13
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 766
    Height = 64
    Align = alTop
    TabOrder = 0
    ExplicitWidth = 772
    object Label1: TLabel
      Left = 15
      Top = 25
      Width = 71
      Height = 13
      Caption = 'Parola chiave :'
    end
    object Label2: TLabel
      Left = 299
      Top = 25
      Width = 46
      Height = 13
      Caption = 'Cerca in :'
    end
    object EditKeyword: TEdit
      Left = 88
      Top = 22
      Width = 100
      Height = 21
      TabOrder = 0
      OnKeyDown = EditKeywordKeyDown
    end
    object ButtonSearch: TButton
      Left = 194
      Top = 20
      Width = 75
      Height = 25
      Caption = '&Cerca'
      TabOrder = 1
      OnClick = ButtonSearchClick
    end
    object ComboBoxSearch: TComboBox
      Left = 351
      Top = 22
      Width = 380
      Height = 21
      Style = csDropDownList
      TabOrder = 2
    end
  end
  object PanelClient: TPanel
    Left = 0
    Top = 64
    Width = 766
    Height = 313
    Align = alClient
    TabOrder = 1
    ExplicitWidth = 772
    ExplicitHeight = 322
    object RichEdit: TRichEdit
      Left = 1
      Top = 1
      Width = 776
      Height = 329
      Align = alClient
      BevelKind = bkSoft
      BevelWidth = 16
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
      WantReturns = False
      OnSelectionChange = RichEditSelectionChange
    end
  end
  object PanelBottom: TPanel
    Left = 0
    Top = 377
    Width = 766
    Height = 48
    Align = alBottom
    TabOrder = 2
    ExplicitTop = 386
    ExplicitWidth = 772
    object ButtonOk: TButton
      Left = 15
      Top = 12
      Width = 75
      Height = 25
      Caption = '&Chiudi'
      TabOrder = 0
      OnClick = ButtonOkClick
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 425
    Width = 766
    Height = 19
    Panels = <
      item
        Width = 256
      end>
    ExplicitTop = 434
    ExplicitWidth = 772
  end
end