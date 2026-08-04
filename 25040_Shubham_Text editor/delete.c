#include "file_ops.h"
#include "redo_undo.h"
#include "text_ops.h"
#include "curser_navigations.h"
#include "display_search.h"
extern DynamicArrayStack undoStack;
extern DynamicArrayStack redoStack;
void deleteCharacters(TextEditor *editor, int length)
{
    int i=0;
    if(editor->head == NULL)
    {
        return;
    }
    char str[100];
    if((editor->cursor->line[editor->cursorPos])=='\0')
    {
        strcpy(str,editor->cursor->line + (editor->cursorPos-length));
        Action temp;
        temp.cur = editor->cursor;
        temp.cursorLine = editor->cursorLine;
        editor->cursorLine--;
        strcpy(temp.operation,"delete");
        strcpy(temp.text,str);
        temp.cursorPos = editor->cursorPos - strlen(str);
        pushStack(&undoStack,temp);
        editor->cursor->line[(editor->cursorPos)-length]='\0';
    }
    else
    {
        strcpy(str,editor->cursor->line+(editor->cursorPos-length));    
        Action temp;
        temp.cur = editor->cursor;
        temp.cursorLine = editor->cursorLine;
        editor->cursorLine--;
        strcpy(temp.operation,"delete");
        strcpy(temp.text,str);
        temp.cursorPos = editor->cursorPos - strlen(str);
        pushStack(&undoStack,temp);
        
        editor->cursor->line[(editor->cursorPos)-length]='\0';
        strcpy((editor->cursor->line)+editor->cursorPos,str);
    }
}
void deleteLine(TextEditor *editor)
{
    if(editor->head == NULL)
    {
        return;
    }
    char str[100];
    if((editor->cursor->next == NULL)&&(editor->cursor->prev == NULL))
    {
        strcpy(str,editor->cursor->line);
        Action temp;
        temp.cur = editor->cursor;
        temp.cursorLine = editor->cursorLine;
        editor->cursorLine--;
        strcpy(temp.operation,"delete");
        strcpy(temp.text,str);
        temp.cursorPos = 0;
        pushStack(&undoStack,temp);

        free(editor->cursor);
        editor->cursor = NULL;
        editor->head = NULL;
        editor->cursorLine =0;
        editor->cursorPos=0;
        editor->tail = NULL;
        
        return;
    }
    else if(editor->cursor->next == NULL)
    {
        strcpy(str,editor->cursor->line);
        Action t;
        t.cur = editor->cursor;
        t.cursorLine = editor->cursorLine;
        editor->cursorLine--;
        strcpy(t.operation,"delete");
        strcpy(t.text,str);
        t.cursorPos = 0;
        pushStack(&undoStack,t);
        Node* temp = editor->cursor;
        editor->cursor = editor->cursor->prev;
        editor->cursor->next = NULL;
        editor->cursorLine =0;
        editor->cursorPos=0;
        free(temp);
        return;
    }
    Action tp;
    tp.cur = editor->cursor;
    tp.cursorLine = editor->cursorLine;
    strcpy(tp.operation,"delete");
    strcpy(tp.text,str);
    tp.cursorLine = editor->cursorLine;
    editor->cursorLine--;
    tp.cursorPos = 0;
    pushStack(&undoStack,tp);

    strcpy(str,editor->cursor->line);
    Node *temp = editor->cursor;
    editor->cursor->next->prev = editor->cursor->prev;
    editor->cursor->prev->next = editor->cursor->next;
    editor->cursor = editor->cursor->next;
    editor->cursorLine--;
    editor->cursorPos=0;
    free(editor->cursor);


    
   return;

}
// undoStack;
// extern DynamicArrayStack redoStack;
void delete_text_editor(TextEditor *editor) //this function is to delete the dynamic memory
{
    Node *temp = editor->head;
    while(temp != NULL)
    {
        Node *temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    
}