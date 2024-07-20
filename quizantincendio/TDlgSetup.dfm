object DlgSetup: TDlgSetup
  Left = 0
  Top = 0
  Caption = 'Quiz Patente Nautica Setup :'
  ClientHeight = 216
  ClientWidth = 512
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 14
    Width = 421
    Height = 200
  end
  object LabelQuizCount: TLabel
    Left = 34
    Top = 106
    Width = 143
    Height = 13
    Caption = 'Numero di domande per quiz :'
  end
  object LabelChoice: TLabel
    Left = 34
    Top = 37
    Width = 128
    Height = 13
    Caption = 'Modalita'#39' del questionario :'
  end
  object ButtonOk: TButton
    Left = 435
    Top = 25
    Width = 75
    Height = 25
    Caption = '&Ok'
    TabOrder = 0
    OnClick = ButtonOkClick
  end
  object EditQuizCount: TEdit
    Left = 181
    Top = 103
    Width = 48
    Height = 21
    TabOrder = 1
    Text = '20'
    OnKeyDown = EditQuizCountKeyDown
  end
  object ComboBoxChoice: TComboBox
    Left = 30
    Top = 53
    Width = 380
    Height = 21
    Style = csDropDownList
    DropDownCount = 16
    TabOrder = 2
    OnChange = ComboBoxChoiceChange
  end
  object CheckBoxCorrectInstantly: TCheckBox
    Left = 34
    Top = 153
    Width = 123
    Height = 17
    Caption = '&Corregge Subito'
    Checked = True
    State = cbChecked
    TabOrder = 3
  end
  object CheckBoxAutoScroll: TCheckBox
    Left = 34
    Top = 185
    Width = 97
    Height = 17
    Caption = '&Autoscorrimento'
    Checked = True
    State = cbChecked
    TabOrder = 4
  end
end
