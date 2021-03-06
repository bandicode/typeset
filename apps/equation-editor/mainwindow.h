// Copyright (C) 2020 Vincent Chambrin
// This file is part of the 'typeset' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef LIBTYPESET_EQEDITOR_MAINWINDOW_H
#define LIBTYPESET_EQEDITOR_MAINWINDOW_H

#include <QWidget>

class QComboBox;
class QCheckBox;
class QLabel;
class QPlainTextEdit;
class QSpinBox;

class EquationEditorRenderWidget;
class FontTreeWidget;
class RecordingTypesetEngine;
class SuggestionBar;

class MainWindow : public QWidget
{
  Q_OBJECT
public:
  explicit MainWindow();
  ~MainWindow();

protected:
  void fillSuggestionBar();
  QWidget* createSettingsWidget();


protected Q_SLOTS:
  void onSuggestionSelected(const std::string& str);
  void onTextChanged();
  void onShowOnlyUsedFontDimenChanged();
  void onDrawCharChanged();
  void onDrawCharBoxesChanged();
  void onDrawListBoxChanged();
  void onDrawBaselinesChanged();

protected:
  void processText();

private:
  std::shared_ptr<RecordingTypesetEngine> m_engine;
  QCheckBox* m_drawchars_checkbox;
  QCheckBox* m_drawcharbox_checkbox;
  QCheckBox* m_drawlistbox_checkbox;
  QCheckBox* m_drawbaselines_checkbox;
  QCheckBox* m_showonlyused_checkbox;
  FontTreeWidget* m_font_treewidget;
  EquationEditorRenderWidget* m_renderwidget;
  SuggestionBar* m_suggestionbar;
  QPlainTextEdit* m_textedit;
  QLabel* m_report_widget;
};

#endif // LIBTYPESET_EQEDITOR_MAINWINDOW_H
