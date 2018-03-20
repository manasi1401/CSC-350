/*************************************************************************//**
 * @file
 *
 * @brief Defines the functions for the menu 
 *****************************************************************************/
#include "mouse.h"

MouseEvent::MouseEvent(int x, int y, int b, int s) 
   : x_pos(x), y_pos(y), button(b), state(s) {}
/***************************************************************************//**
* @author Peterson, Shawn
* @par Description:
* 
* The MouseEvent::action is a function used to make the menu bar in the 
* paint program objects to be selected
*
* @param[in] programState - a structure holding the all the info about the shape
******************************************************************************/
void MouseEvent::action(State &programState)
{
    float max = glutGet(GLUT_WINDOW_HEIGHT);
  int  boxD = glutGet(GLUT_WINDOW_HEIGHT)/8;
  float height =glutGet(GLUT_WINDOW_HEIGHT)/8;
  float width = height;
  int y = this-> y_pos;
  int x = this-> x_pos;
  int s = this-> state;
  int b = this-> button;

   //Menu Bar
   //delete programState.demo; Boarder color select
    if(b == GLUT_LEFT_BUTTON)
        MouseBoarder(x, y, boxD, programState);
        
    //Fill color select    
    if(b == GLUT_RIGHT_BUTTON)
       MouseFill(x, y, boxD, programState);   
           
    //Shape select 
    if(s == GLUT_UP)
    {  
        if(x <= boxD*2)
        {
        //circle Select
        if(x <= boxD && y>=boxD*5+1 && y <= boxD*6)
              programState.shapeSelc = 1;
                      
        //square Select
        if(x <= boxD && y>=boxD*6+1 && y <= boxD*7)
             programState.shapeSelc = 2;
                 
        //Line Select
        if(x >= boxD && y>=boxD*7+1 && y <= boxD*8)
             programState.shapeSelc = 3;
        
        //Filled circle Select
        if(x >= boxD && y>=boxD*5+1 && y <= boxD*6)
             programState.shapeSelc = 4;      
                     
        //Filled square Select
        if(x >= boxD && y >= boxD*6+1 && y <= boxD*7)
            programState.shapeSelc = 5;
        }
    }
    
    delete programState.demo;
    programState.demo = nullptr;
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer
	glLoadIdentity();	
	eventDispatcher(new DisplayEvent());
	//decides the sample shape to be drawn in the pallet
    if (programState.shapeSelc == 1)
   { 
    Ellipse * elli= new Ellipse (width*(0.3), width*(0.3), width/2, height* (7.5),programState.boarder);
    programState.demo = elli;
   }
   if (programState.shapeSelc == 2)
   { 
    Rectangle * rect= new Rectangle (width*(0.2), 7.2*height, width*0.8, height* (7.8),programState.boarder);
    programState.demo = rect;
   }
   if (programState.shapeSelc == 3)
   { 
    Line * line= new Line (width*(0.2), 7.2*height, width*0.8, height* (7.8),programState.boarder);
    programState.demo = line;
   }
   if (programState.shapeSelc == 4)
   { 
    Ellipse * ellif= new Ellipse (width*(0.3), width*(0.3), width/2, height* (7.5),programState.boarder, programState.fill, true);
    programState.demo = ellif;
   }
   if (programState.shapeSelc == 5)
   { 
    Rectangle * rectf= new Rectangle (width*(0.2), 7.2*height, width*0.8, height* (7.8),programState.boarder, programState.fill, true);
    programState.demo = rectf;
   }
    
    eventDispatcher(new InitEvent());
   if(s == GLUT_DOWN)
   {
        programState.downX = x;
        programState.downY = y;
   }
   if(s == GLUT_UP && b==GLUT_RIGHT_BUTTON && x >= boxD*2){
    float xcoord = (float)x;
    float ycoord =(float)y;
    Shape *tobemoved = nullptr;
    for (Shape *shape : programState.shapes){
        if(shape->contains(programState.downX, programState.downY)){
         if(shape->getDist()<max)
            {
                max= shape->getDist();
                tobemoved =shape;
            }
   
        }
        
    }
    //moves the shape thats closest to the click and redraw the screen
    if(tobemoved!=nullptr){
      tobemoved->moveshape(xcoord, ycoord);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer 
	   glLoadIdentity();	
        eventDispatcher(new DisplayEvent());}
   }
   // adds the shape to the state list 
   if(s == GLUT_UP && b == GLUT_LEFT_BUTTON)
   {
        if(x >= boxD*2)
        {
               int x1 = abs(x - programState.downX) ;
               int y1 = abs(y - programState.downY) ;
               int testX = abs(x1 - programState.upX);
               int testY = abs(y1 - programState.upY);
                 
              if(testX != 0 && testY != 0)
              {
                  if(programState.shapeSelc == 1)
                  {  
                     Ellipse *ellipse =new Ellipse(x1, y1, programState.downX, programState.downY, programState.boarder, programState.fill)    ;
                     programState.shapes.push_back(ellipse);
                  }
                  
                  if(programState.shapeSelc == 2)
                  { 
                    Rectangle *rect =new Rectangle(x,y,programState.downX,programState.downY, programState.boarder, programState.fill, false);
                     programState.shapes.push_back(rect);
                  }
                   
                   if(programState.shapeSelc == 3)
                  {   
                     Line *line =new Line (programState.downX, programState.downY, x, y, programState.boarder);
                     programState.shapes.push_back(line);
                  }
                   
                   if(programState.shapeSelc == 4)
                  {
                   Ellipse *ellipsef =new Ellipse(x1, y1, programState.downX, programState.downY, programState.boarder, programState.fill, true);
                   programState.shapes.push_back(ellipsef);
                  }
                   
                   if(programState.shapeSelc == 5)
                  {   
                    Rectangle *rectf =new Rectangle(x,y,programState.downX,programState.downY, programState.boarder, programState.fill, true);   
                    programState.shapes.push_back(rectf);           
                  }
                  
              
             } 
             
        }   
    }
        
    eventDispatcher(new DisplayEvent());
}

/***************************************************************************//**
* @author Peterson, Shawn
* @brief MouseFill is a function that is used to select the fill color
*  for the shape
*
* @param[in]   x     - a variable holding the position of the mouse on the x 
*  axis
* @param[in]   y     - a variable holding the position of the mouse on the y 
*  axis
* @param[in]   boxD  - a variable holding the demensions of the menu box
*
* @param[in] programState - a structure holding the all the info about the shape
******************************************************************************/

void MouseFill(int x, int y, int boxD, State &programState)
{

if(x <= boxD*2+1)
{      
        //lowest left box 1
        if(x < boxD && y <= boxD)
        {
            programState.fill[0] = 1.0;
            programState.fill[1] = 0.0;
            programState.fill[2] = 0.0;
        }
  
        //second box up from bottom left box 2
        if(x <= boxD && y>=boxD+1 && y <= boxD*2)
        {
            programState.fill[0] = 0.0;
            programState.fill[1] = 1.0;
            programState.fill[2] = 0.0;
        }
          
        //third box up from bottom left box 3
        if(x <= boxD && y>=boxD*2+1 && y <= boxD*3)
        {
            programState.fill[0] = 1.0;
            programState.fill[1] = 0.0;
            programState.fill[2] = 1.0;
        }
  
        //fourth box up from bottom left box 4 
        if(x <= boxD && y>=boxD*3+1 && y <= boxD*4)
        {
            programState.fill[0] = 0.752941;
            programState.fill[1] = 0.752941;
            programState.fill[2] = 0.752941;
        }
         
        //fith box up from bottom left box 5
        if(x <= boxD && y>boxD*4+1 && y <= boxD*5)
        {
            programState.fill[0] = 1.0;
            programState.fill[1] = 0.5;
            programState.fill[2] = 0.0;
        }
          
        //lowest right box 6 
        if(x >= boxD+1 && y <= boxD)
        {
            programState.fill[0] = 1.0;
            programState.fill[1] = 1.0;
            programState.fill[2] = 1.0;
        }
          
        //second  box up from bottom right box 7 
        if(x >= boxD+1  && y>=boxD+1 && y <= boxD*2)
        {
            cout << "Yellow Selcted" << endl;
            programState.fill[0] = 1.0;
            programState.fill[1] = 1.0;
            programState.fill[2] = 0;
        }
          
        //third box up from bottom right box 8 
        if(x >= boxD+1 && y>=boxD*2+1 && y <= boxD*3)
        {
            programState.fill[0] = 0;
            programState.fill[1] = 1.0;
            programState.fill[2] = 1.0;
        }
          
        //fourth box up from bottom right box 9 
        if(x >= boxD+1 && y>=boxD*3+1 && y <= boxD*4)
        {
            programState.fill[0] = 0.647059;
            programState.fill[1] = 0.164706; 
            programState.fill[2] = 0.164706;
        }
          
        //fith box up from bottom right box 10 
        if(x >= boxD+1 && y>=boxD*4+1 && y <= boxD*5)
        {
            programState.fill[0] = 0.8; 
            programState.fill[1] = 0.498039;
            programState.fill[2] = 0.196078;
        }   
    }
}

/***************************************************************************//**
* @author Peterson, Shawn
* @brief MouseBoarder is a function that is used to selec the boarder color
*  for the shape
*
* @param[in]   x     - a variable holding the position of the mouse on the x 
*  axis
* @param[in]   y     - a variable holding the position of the mouse on the y 
*  axis
* @param[in]   boxD  - a variable holding the demensions of the menu box
* @param[in] programState - a structure holding the all the info about the shape
******************************************************************************/
void MouseBoarder(int x, int y, int boxD, State &programState)
{
 if(x <= boxD*2+1)
       {      
            //lower left box 1
            if(x < boxD && y <= boxD)
             {
                cout << "Red Selcted" << endl;
                programState.boarder[0] = 1.0;
                programState.boarder[1] = 0.0;
                programState.boarder[2] = 0.0;
             }
      
            //second from bottom left box
            if(x <= boxD && y>=boxD+1 && y <= boxD*2)
            {
                cout << "Green Selcted" << endl;
                programState.boarder[0] = 0.0;
                programState.boarder[1] = 1.0;
                 programState.boarder[2] = 0.0;
            }
      
            //third from bottom left box
            if(x <= boxD && y>=boxD*2+1 && y <= boxD*3)
             {
                cout << "Purple Selcted" << endl;
                programState.boarder[0] = 1.0;
                 programState.boarder[1] = 0.0;
                programState.boarder[2] = 1.0;
            }
      
            //fourth from bottom left box
            if(x <= boxD && y>=boxD*3+1 && y <= boxD*4)
            {
                cout << "Grey Selcted" << endl;
                programState.boarder[0] = 0.752941;
                programState.boarder[1] = 0.752941;
                programState.boarder[2] = 0.752941;
            }
      
            //fith from bottom left box
            if(x <= boxD && y>boxD*4+1 && y <= boxD*5)
            {
                cout << "Orange Selcted" << endl;
                programState.boarder[0] = 1.0;
                programState.boarder[1] = 0.5;
                programState.boarder[2] = 0.0;
            }
      
            //lower right box 10
            if(x >= boxD+1 && y <= boxD)
            {
                cout << "White Selcted" << endl;
                programState.boarder[0] = 1.0;
                programState.boarder[1] = 1.0;
                programState.boarder[2] = 1.0;
            }
      
            //second from bottom right box
            if(x >= boxD+1  && y>=boxD+1 && y <= boxD*2)
            {
                cout << "Yellow Selcted" << endl;
                programState.boarder[0] = 1.0;
                programState.boarder[1] = 1.0;
                programState.boarder[2] = 0;
            }
      
            //third from bottom right box
            if(x >= boxD+1 && y>=boxD*2+1 && y <= boxD*3)
            {
                cout << "Teal Selcted" << endl;
                programState.boarder[0] = 0;
                programState.boarder[1] = 1.0;
                programState.boarder[2] = 1.0;
            }
      
            //fourth from bottom right box
            if(x >= boxD+1 && y>=boxD*3+1 && y <= boxD*4)
            {
                cout << "Dark Red Selcted" << endl;
                 programState.boarder[0] = 0.647059;
                programState.boarder[1] = 0.164706; 
                programState.boarder[2] = 0.164706;
            }
      
            //fith from bottom right box
            if(x >= boxD+1 && y>=boxD*4+1 && y <= boxD*5)
            {
                cout << "Gold Selcted" << endl;
                programState.boarder[0] = 0.8; 
                programState.boarder[1] = 0.498039; 
                programState.boarder[2] = 0.196078;
             
            }
            
        } 
}

