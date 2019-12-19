import cv2 as cv
import numpy as np
import sys

from skimage.color import rgb2lab, deltaE_cie76

#Get picture filename from terminal args
filename = sys.argv[1]

no_op = True if len(sys.argv) > 2 and sys.argv[2] == "white" else False


img     = cv.imread(filename)
lab_img = rgb2lab(img)
white   = np.ones(shape=img.shape)



#Draw a rectangle in img (the binarized picture)
def drawRectangle(p1,p2):
    cv.rectangle(white if no_op else img, tuple(p1),tuple(p2),(0,0,0),1)

def count_similarities(segment):
    if segment.size == 0: return True
    lab_segment     = segment
    # print(lab_segment.shape, lab_segment.size)
    pivot_pixel     = lab_segment[0,0]
    for i in lab_segment:
        for j in i:
            if deltaE_cie76(pivot_pixel, j) > 8: return False
    
    return True
    

#QuadTree Node:     
# Draws a rectangle when its created
class QNode:
    #In: Two points of a quadrant
    #   p1: Left - Up point
    #   p2: Right- Down point

    def __init__(self,p1,p2):
        self.p1 = p1
        self.p2 = p2
        self.color = 0
        self.hijos = [None] * 4
        # print("Created QNode")
        self.setColor()
        drawRectangle(self.p1,self.p2)

    #Set a color between -1 (gray), 0 (black) and 1(white) to the node
    def setColor(self):
        # Counts all non-zeros inside the quadrant (between p1 and p2)
        # suma = np.count_nonzero(img[ self.p1[1] : self.p2[1] , self.p1[0] : self.p2[0] ])
        similarity = count_similarities(lab_img[ self.p1[1] : self.p2[1] , self.p1[0] : self.p2[0] ])
        # print("Check simi: ",similarity)
        self.simi  = similarity
        #Total of pixels in the quadrant
        # total = abs((self.p2[1] - self.p1[1]) * (self.p2[0] - self.p1[0]))

        if  similarity      : self.color = 1     #All pixels are similar
        else                : self.color = -1    #If there are less non-zeros than zeros

    #Calculate auxiliar points to divide a quadrant
    #and create children nodes
    def dividir(self):
        #Center of quadrant
        centro = self.p1 + (self.p2 - self.p1)//2

        #WASD points (Up - Down, Left - Right)
        arriba = np.array([ centro[0] , self.p1[1] ])
        abajo  = np.array([ centro[0] , self.p2[1] ])

        izquierda = np.array([ self.p1[0] , centro[1] ])
        derecha   = np.array([ self.p2[0] , centro[1] ])

        #Creates children nodes with WASD points  
        self.hijos[0] = QNode(self.p1,centro)
        self.hijos[1] = QNode(arriba,derecha)
        self.hijos[2] = QNode(centro,self.p2)
        self.hijos[3] = QNode(izquierda,abajo)

    #Divide a Quadrant until the lenght of quadrant is 1 pixel
    # If Quadrant color is complete white or black then no divide
    def deepDivide(self):
        #Lenght of quadrant
        if np.array_equal(self.p2-self.p1,(1,1)): return
        #If the color is gray then divide
        # print("Check color: ", self.color)
        if self.color == -1: self.dividir()

        #For progressive visualization
        # cv.imshow("lena",white)
        # cv.waitKey(1)

        if self.hijos == [None] * 4: return
        # For each children with gray Color (-1) divide it
        #print("loading...")
        for i in self.hijos:
            if i.color == -1:
                i.deepDivide()

#QuadTree Class
class QTree:    
    def __init__(self): 
        self.imagen = img
        #The root node is on all the picture
        self.root = QNode(np.array((0,0)), np.array(img.shape[1::-1]))
        #Show binarized image
        
        cv.imshow("lena",img)
        print("Press any key to start...\n")
        cv.waitKey(0)


        #Execute deepDivide
        print("Creating QuadTree...\n")
        self.root.deepDivide()

        #Show after deepDivide

        cv.imshow("lena", white if no_op else img)
        print("Press any key to exit...\n")
        cv.imwrite("quad.jpg", white if no_op else img)
        cv.waitKey(0)
        cv.destroyAllWindows()


t = QTree()