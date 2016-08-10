#ifndef LINENUMBEREDITOR_H
#define LINENUMBEREDITOR_H

#include <QWidget>

#include <QPlainTextEdit>

class LineNumberEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    LineNumberEditor(QWidget *parent= 0);
    ~LineNumberEditor(){}

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect&, int);

private:
    QWidget *lineNumberArea;
};

class LineNumberArea : public QWidget
  {
  public:
      LineNumberArea(LineNumberEditor *editor) : QWidget(editor) {
          m_editor = editor;
      }

      QSize sizeHint() const Q_DECL_OVERRIDE {
          return QSize(m_editor->lineNumberAreaWidth(), 0);
      }

  protected:
      void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
          m_editor->lineNumberAreaPaintEvent(event);
      }

  private:
      LineNumberEditor *m_editor;
  };

#endif // LINENUMBEREDITOR_H
