#include "definitions.h"
#include "load_obj.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

//comenzar programa con alguna transformacion activa
//si se activa una, se desactiva otra

extern object3d * _first_object;
extern object3d * _selected_object;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

#define ANGULO 18.0

bool traslacion, rotacion, escalado, mundoSR, objetoSR;
int contm, conte, contr, contg, contl;
list_matrix *newptr;

/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help(){
    printf("KbG Irakasgaiaren Praktika. Programa honek 3D objektuak \n");
    printf("aldatzen eta bistaratzen ditu.  \n\n");
    printf("\n\n");
    printf("FUNTZIO NAGUSIAK \n");
    printf("<?>\t\t Laguntza hau bistaratu \n");
    printf("<ESC>\t\t Programatik irten \n");
    printf("<F>\t\t Objektua bat kargatu\n");
    printf("<TAB>\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<DEL>\t\t Hautatutako objektua ezabatu\n");
    printf("<CTRL + ->\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t Bistaratze-eremua txikitu\n");
    printf("<M/m>\t\t Activar traslacion\n");
    printf("<B/b>\t\t Activar rotacion\n");
    printf("<T/t>\t\t Activar escalado\n");
    printf("<G/g>\t\t Activar transformaciones en SR mundo\n");
    printf("<L/l>\t\t Activar transformaciones en SR objeto\n");
    printf("¡¡¡TRASLACION ACTIVADA POR DEFECTO!!!\n");
    printf("\n\n");
}


void traslation(float x, float y, float z){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(x, y, z);
    glMultMatrixf(_selected_object->list_matrix->m);
    newptr = malloc(sizeof(list_matrix));
    glGetFloatv(GL_MODELVIEW_MATRIX, newptr->m);
    newptr->nextptr = _selected_object->list_matrix;
    _selected_object->list_matrix = newptr;
    glutPostRedisplay();
}

void global_traslation(float x, float y, float z){
    glLoadIdentity();
    glTranslatef(x, y, z);
    glMultMatrixf(_selected_object->list_matrix->m);
    newptr = malloc(sizeof(list_matrix));
    glGetFloatv(GL_MODELVIEW_MATRIX, newptr->m);
    newptr->nextptr = _selected_object->list_matrix;
    _selected_object->list_matrix = newptr;
    glutPostRedisplay();
    
}

void rotation(GLfloat x, GLfloat y, GLfloat z){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(ANGULO, x, y, z);
    glMultMatrixf(_selected_object->list_matrix->m);
    newptr = malloc(sizeof(list_matrix));
    glGetFloatv(GL_MODELVIEW_MATRIX, newptr->m);
    newptr->nextptr = _selected_object->list_matrix;
    _selected_object->list_matrix = newptr;
    glutPostRedisplay();
}

void global_rotation(GLfloat x, GLfloat y, GLfloat z){
    glLoadIdentity();
    glRotatef(ANGULO, x, y, z);
    glMultMatrixf(_selected_object->list_matrix->m);
    newptr = malloc(sizeof(list_matrix));
    glGetFloatv(GL_MODELVIEW_MATRIX, newptr->m);
    newptr->nextptr = _selected_object->list_matrix;
    _selected_object->list_matrix = newptr;
    glutPostRedisplay();
}

void scalation(float x, float y, float z){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(x, y, z);
    glMultMatrixf(_selected_object->list_matrix->m);
    newptr = malloc(sizeof(list_matrix));
    glGetFloatv(GL_MODELVIEW_MATRIX, newptr->m);
    newptr->nextptr = _selected_object->list_matrix;
    _selected_object->list_matrix = newptr;
    glutPostRedisplay();
}

void global_scalation(float x, float y, float z){
    glLoadIdentity();
    glScalef(x, y, z);
    glMultMatrixf(_selected_object->list_matrix->m);
    newptr = malloc(sizeof(list_matrix));
    glGetFloatv(GL_MODELVIEW_MATRIX, newptr->m);
    newptr->nextptr = _selected_object->list_matrix;
    _selected_object->list_matrix = newptr;
    glutPostRedisplay();
}

void free_ptr(object3d *object){
    int i;
    for (i = 0; i < object->num_faces; i++)
                free(object->face_table[i].vertex_table);
                

            free(object->face_table);
            free(object->vertex_table);
            free(object);
}


/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void keyboard(unsigned char key, int x, int y) {

    char* fname = malloc(sizeof (char)*128); /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    
    traslacion = false;
    rotacion = false;
    escalado = false;
    object3d *auxiliar_object = 0;
    GLdouble wd,he,midx,midy;

    list_matrix *aux_list;


    switch (key) {
    case 'f':
    case 'F':
        /*Ask for file*/
        contm++;
        printf("%s", KG_MSSG_SELECT_FILE);
        scanf("%s", fname);
        glLoadIdentity();
        /*Allocate memory for the structure and read the file*/
        auxiliar_object = (object3d *) malloc(sizeof (object3d));
        read = read_wavefront(fname, auxiliar_object);
        switch (read) {
        /*Errors in the reading*/
        case 1:
            printf("%s: %s\n", fname, KG_MSSG_FILENOTFOUND);
            break;
        case 2:
            printf("%s: %s\n", fname, KG_MSSG_INVALIDFILE);
            break;
        case 3:
            printf("%s: %s\n", fname, KG_MSSG_EMPTYFILE);
            break;
        /*Read OK*/
        case 0:
            /*Insert the new object in the list*/
            aux_list = (list_matrix *)malloc(sizeof(list_matrix));
            glLoadIdentity();
            glGetFloatv(GL_MODELVIEW_MATRIX, aux_list->m);
            aux_list->nextptr = 0;
            auxiliar_object->list_matrix = aux_list;

            auxiliar_object->next = _first_object;
            _first_object = auxiliar_object;
            _selected_object = _first_object;
            printf("%s\n",KG_MSSG_FILEREAD);
            break;
        }
        break;

    case 9: /* <TAB> */
        _selected_object = _selected_object->next;
        /*The selection is circular, thus if we move out of the list we go back to the first element*/
        if (_selected_object == 0) _selected_object = _first_object;
        break;

    case 127: /* <SUPR> */
        /*Erasing an object depends on whether it is the first one or not*/
        if (_selected_object == _first_object)
        {
            /*To remove the first object we just set the first as the current's next*/
            _first_object = _first_object->next;
            /*Once updated the pointer to the first object it is save to free the memory*/
            
            free_ptr(_selected_object);
            /*Finally, set the selected to the new first one*/
            _selected_object = _first_object;
        } else {
            /*In this case we need to get the previous element to the one we want to erase*/
            auxiliar_object = _first_object;
            while (auxiliar_object->next != _selected_object)
                auxiliar_object = auxiliar_object->next;
            /*Now we bypass the element to erase*/
            auxiliar_object->next = _selected_object->next;
            /*free the memory*/
                


            free_ptr(_selected_object);
            /*and update the selection*/
            _selected_object = auxiliar_object;
        }
        break;

    case '-':
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL || glutGetModifiers() == GLUT_ACTIVE_CTRL){

            /*Increase the projection plane; compute the new dimensions*/
            wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates*/
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane*/
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
        }
        break;

    case '+':
        //INPLEMENTA EZAZU CTRL + + KONBINAZIOAREN FUNTZIOANLITATEA
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL || glutGetModifiers() != GLUT_ACTIVE_CTRL){
            /*Increase the projection plane; compute the new dimensions*/
            wd=(_ortho_x_max-_ortho_x_min)*KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)*KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates*/
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane*/
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
        }
        break;

    case 'm':
    case 'M':
        contm++;
        if (contm % 2 != 0){
            traslacion = true;
            rotacion = false;
            escalado = false;
            printf("Activada la traslacion. Desactivadas el resto\n");
            contr = 0;
            conte = 0;
        }else{
            printf("Desactivada la traslacion\n");
            traslacion = false;
        }
        break;

    case 'b':
    case 'B':
        contr++;
        if (contr % 2 != 0){
            printf("Activada la rotacion. Desactivadas el resto\n");
            contm = 0;
            conte = 0;
            rotacion = true;
            traslacion = false;
            escalado = false;
        } else {
            printf("Desactivada la rotacion\n");
            rotacion = false;
        }
        break;

    case 't':
    case 'T':
        conte++;
        if (conte % 2 != 0){
            printf("Activado el escalado. Desactivadas el resto\n");
            contm = 0;
            contr = 0;
            escalado = true;
            rotacion = false;
            traslacion = false;
        } else {
            printf("Desactivado el escalado\n");
            escalado = false;
        }
        break;

    case 'g':
    case 'G':
        contg++;
        if (contg % 2 != 0){
            printf("Activadas transformaciones en SR del mundo. Desactivadas SR objeto\n");
            contl = 0;
            contr = 0;
            conte = 0;
            traslacion = true;
            mundoSR = true;
            objetoSR = false;
        } else {
            printf("Desactivadas transformaciones en SR mundo\n");
            mundoSR = false;
        }
        break;

    case 'l':
    case 'L':
        contl++;
        if (contl % 2 != 0){
            printf("Activadas transformaciones en SR objeto. Desactivadas SR mundo\n");
            contg = 0;
            contr = 0;
            conte = 0;
            objetoSR = true;
            traslacion = true;
            mundoSR = false;
        } else {
            printf("Desactivadas transformaciones en SR objeto\n");
            objetoSR = false;
        }
        break;


    case '?':
        print_help();
        break;

    case 27: /* <ESC> */
        exit(0);
        break;

    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
    }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}

void SpecialInput(int key, int x, int y)
{
switch(key)
{
case GLUT_KEY_UP:
    if (objetoSR){
        if (traslacion)
            traslation(0.0f, 1.0f, 0.0f);
        else if (rotacion)
            rotation(1.0f, 0.0f, 0.0f);
        else if (escalado)
            scalation(1.0f, 2.0f, 1.0f);
    } else if (mundoSR){
        if (traslacion)
            global_traslation(0.0f, 1.0f, 0.0f);
        else if(rotacion)
            global_rotation(1.0f, 0.0f, 0.0f);
        else if (escalado)
            global_scalation(1.0f, 2.0f, 1.0f);
    }
break;

case GLUT_KEY_DOWN:
    if (objetoSR){
        if (traslacion)
            traslation(0.0f, -1.0f, 0.0f);
        else if (rotacion)
            rotation(-1.0f, 0.0f, 0.0f);
        else if (escalado)
            scalation(1.0f, 0.5f, 1.0f);
    } else if (mundoSR){
        if (traslacion)
            global_traslation(0.0f, -1.0f, 0.0f);
        else if (rotacion)
            global_rotation(-1.0f, 0.0f, 0.0f);
        else if (escalado)
            global_scalation(1.0f, 0.5f, 1.0f);
    }
break;

case GLUT_KEY_LEFT:
    if (objetoSR){
        if (traslacion)
            traslation(-1.0f, 0.0f, 0.0f);
        else if (rotacion)
            rotation(0.0f, -1.0f, 0.0f);
        else if (escalado)
            scalation(0.5f, 1.0f, 1.0f);
    } else if (mundoSR){
        if (traslacion)
            global_traslation(-1.0f, 0.0f, 0.0f);
        else if (rotacion)
            global_rotation(0.0f, -1.0f, 0.0f);
        else if (escalado)
            global_scalation(0.5f, 1.0f, 1.0f);
    }


break;

case GLUT_KEY_RIGHT:
    if (objetoSR){
        if (traslacion)
            traslation(1.0f, 0.0f, 0.0f);
        else if (rotacion)
            rotation(0.0f, 1.0f, 0.0f);
        else if (escalado)
            scalation(2.0f, 1.0f, 1.0f);
    } else if (mundoSR){
        if (traslacion)
            global_traslation(1.0f, 0.0f, 0.0f);
        else if (rotacion)
            global_rotation(0.0f, 1.0f, 0.0f);
        else if (escalado)
            global_scalation(2.0f, 1.0f, 1.0f);
    }

break;

case GLUT_KEY_PAGE_UP: //tecla Re Pág
    if (objetoSR){
        if (traslacion)
            traslation(0.0f, 0.0f, -1.0f);
        else if (rotacion)
            rotation(0.0f, 0.0f, -1.0f);
        else if (escalado)
            scalation(1.0f, 1.0f, 0.5f); //corregir el escalado
    } else if (mundoSR){
        if (traslacion)
            global_traslation(0.0f, 0.0f, -1.0f);
        else if (rotacion)
            global_rotation(0.0f, 0.0f, -1.0f);
        else if (escalado)
            global_scalation(1.0f, 1.0f, 0.5f);
    }
break;

case GLUT_KEY_PAGE_DOWN: //tecla Av Pág no corregido
    if (objetoSR){
        if (traslacion)
            traslation(0.0f, 0.0f, 1.0f);
        if (rotacion)
            rotation(0.0f, 0.0f, 1.0f);
        if (escalado)
            scalation(1.0f, 1.0f, 2.0f);
    } else if (mundoSR){
        if (traslacion)
            global_traslation(0.0f, 0.0f, 1.0f);
        else if (rotacion)
            global_rotation(0.0f, 0.0f, 1.0f);
        else if (escalado)
            global_scalation(1.0f, 1.0f, 2.0f);
    }
break;
}

glutPostRedisplay();
}