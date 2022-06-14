import os
import pygame
from time import sleep

lc=(150,150,0)#line color

n,nx=[40,30]#nxn tiles, each nx pixels
n=int(n)
nx=int(nx)


def flip():
    pygame.display.flip()
    
pygame.init()
pygame.display.set_caption(u"Map Maker V2")
scr=pygame.display.set_mode((n*nx, n*nx//2))
clock = pygame.time.Clock()# creates a clock

scr.fill((0,34,64)) #background

def line(spos,epos):
    pygame.draw.line(scr,pygame.Color(lc[0],lc[1],lc[2]), spos, epos)

def draw_board(n,nx):
    for i in range(n):
        line((nx*(i+1),0),(nx*(i+1),n*nx))
        line((0,nx*(i+1)),(n*nx,nx*(i+1)))

def inrect(r,x,y):return (r.x<=x and r.right>=x) and (r.y<=y and r.bottom>=y)

class tile:
    def __init__(self,x,y,stat=None):
        self.x=x
        self.y=y
        self.stat=stat
        self.no=1
        self.paint()
        
    def paint(self,color=None):
        if not color:
            if self.stat=="w":
                if self.no >0:
                    scr.blit(pygame.transform.scale(tileI[self.no-1], (nx-1, nx-1)), (self.x*nx+1,self.y*nx+1))
                else:scr.blit(pygame.transform.scale(tileBg[-1*self.no-1], (nx-1, nx-1)), (self.x*nx+1,self.y*nx+1))
            if self.stat==None:
                pygame.draw.rect(scr,(0,34,64),(self.x*nx+1,self.y*nx+1,nx-1,nx-1))
        else:pygame.draw.rect(scr,color,(self.x*nx,self.y*nx,nx,nx))
        flip()
        
tileI=list(range(15))
tileI[0] = pygame.image.load(r'../assets/map/Tiles/Tile (1).png')
tileI[1] = pygame.image.load(r'../assets/map/Tiles/Tile (2).png')
tileI[2] = pygame.image.load(r'../assets/map/Tiles/Tile (3).png')
tileI[3] = pygame.image.load(r'../assets/map/Tiles/Tile (4).png')
tileI[4] = pygame.image.load(r'../assets/map/Tiles/Tile (5).png')
tileI[5] = pygame.image.load(r'../assets/map/Tiles/Tile (6).png')
tileI[6] = pygame.image.load(r'../assets/map/Tiles/Tile (7).png')
tileI[7] = pygame.image.load(r'../assets/map/Tiles/Tile (8).png')
tileI[8] = pygame.image.load(r'../assets/map/Tiles/Tile (9).png')
tileI[9] = pygame.image.load(r'../assets/map/Tiles/Tile (10).png')
tileI[10] = pygame.image.load(r'../assets/map/Tiles/Tile (11).png')
tileI[11] = pygame.image.load(r'../assets/map/Tiles/Tile (12).png')
tileI[12] = pygame.image.load(r'../assets/map/Tiles/Tile (13).png')
tileI[13] = pygame.image.load(r'../assets/map/Tiles/Tile (14).png')
tileI[14] = pygame.image.load(r'../assets/map/Tiles/Tile (15).png')

TOTALBGTILES = 9
tileBg=list(range(TOTALBGTILES))
tileBg[0] = pygame.image.load(r'../assets/map/Tiles/BgTile (1).png')
tileBg[1] = pygame.image.load(r'../assets/map/Tiles/BgTile (2).png')
tileBg[2] = pygame.image.load(r'../assets/map/Tiles/BgTile (3).png')
tileBg[3] = pygame.image.load(r'../assets/map/Tiles/BgTile (4).png')
tileBg[4] = pygame.image.load(r'../assets/map/Tiles/BgTile (5).png')
tileBg[5] = pygame.image.load(r'../assets/map/Tiles/BgTile (6).png')
tileBg[6] = pygame.image.load(r'../assets/map/Tiles/BgTile (7).png')
tileBg[7] = pygame.image.load(r'../assets/map/Tiles/BgTile (8).png')
tileBg[8] = pygame.image.load(r'../assets/map/Tiles/BgTile (9).png')

tiles=list(range(n))
for i in range(n):tiles[i] = [tile(i,k) for k in range(n)]

def loadTiles():
    try: ##TILES
        f = open("map01.dat", 'r');
        x,y = 0, 0
        lines = f.read().split('\n')
        for l in lines:
            for i in l.split():
                if int(i)!=0:
                    tiles[x][y].stat = "w"
                    tiles[x][y].no = int(i)
                    tiles[x][y].paint()
                x+=1
            x = 0
            y+=1
            
        f.close()
    except:pass#raise Exception()
    
    
def drawTiles():
    for y in range(20):
        for x in range(40):
            tiles[x][y].paint()
            
def loadEnts():
    try: ##ENTITIES
        f = open("ents01.dat", 'r');
        fs = f.read()
        f.close()

        for i in fs.split('\n'):
            ws = i.split()
            
            if ws[0] == "PIZZA":
                x = float(ws[1])
                y = float(ws[2])
                spizzas.append([x,y])
                
            if ws[0] == "PLATFORM":
                x = float(ws[1])
                y = float(ws[2])
                xe = float(ws[3])
                ye = float(ws[4])
                splatforms.append([x,y,xe,ye])
                
            if ws[0] == "BLOCK":
                x = float(ws[1])
                y = float(ws[2])
                sblocks.append([x,y])
    except:pass

def drawEnts():
    for p in spizzas:
        x = (p[0]*(n*nx))/2560
        y = (p[1]*(n*nx))/2560
        if len(p) == 2 :
            p.append(pygame.draw.rect(scr,(200,200,10), (x,y,10,10)))
        else:p[-1]=pygame.draw.rect(scr,(200,200,10), (x,y,10,10))

    for p in splatforms:
        xs = p[0]+124
        ys = p[1]+34
        x = (p[0]*(n*nx))/2560
        y = (p[1]*(n*nx))/2560
        xs = (xs*(n*nx))/2560
        ys = (ys*(n*nx))/2560
        xe = (p[2]*(n*nx))/2560
        ye = (p[3]*(n*nx))/2560
        pygame.draw.line(scr,(200,10,200), (x+(62*(n*nx))/2560,y+(17*(n*nx))/2560),(xe+(62*(n*nx))/2560,ye+(17*(n*nx))/2560),5)
        if len(p) == 4 :
            p.append(pygame.draw.rect(scr,(0,0,0), (x,y,xs-x,ys-y)))
        else:p[-1]=pygame.draw.rect(scr,(0,0,0), (x,y,xs-x,ys-y))
        pygame.draw.rect(scr,(0,0,0), (xe-(15*(n*nx))/2560+(62*(n*nx))/2560,ye-(15*(n*nx))/2560+(17*(n*nx))/2560,(30*(n*nx))/2560,(30*(n*nx))/2560))

    for b in sblocks:
        xe = b[0]+64
        ye = b[1]+32
        x = (b[0]*(n*nx))/2560
        y = (b[1]*(n*nx))/2560
        xe = (xe*(n*nx))/2560
        ye = (ye*(n*nx))/2560
        if len(b) == 2 :
            b.append(pygame.draw.rect(scr,(10,10,10), (x,y,xe-x,ye-y)))
        else:b[-1]=pygame.draw.rect(scr,(10,10,10), (x,y,xe-x,ye-y))

spizzas=[]
splatforms=[]
sblocks=[]

loadEnts()

draw_board(n,nx)
loadTiles()
drawTiles()
drawEnts()

last=[]

flip()

ready=2
tileNo=1
putTail=False
draw=False
erase=False
wheeling=False
onMap=True
onMapBg=False
onPlat=False
onBlock=False
onPizza=False
bx,by=0,0

while 1:
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_m:
                onMap = True
                onPizza = False
                onBlock = False
                onPlat = False
                pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_ARROW)
                putTail = False
                x,y = [0,0]
                
            if (event.key == pygame.K_b and onMap):
                onMapBg = not onMapBg
                tileNo=1
                
            if event.key == pygame.K_j:
                onPizza = True
                onMap = False
                onBlock = False
                onPlat = False
                pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_ARROW)
                putTail = False
                x,y = [0,0]

            if event.key == pygame.K_k:
                onPlat = True
                onMap = False
                onBlock = False
                onPizza = False
                
            if event.key == pygame.K_l:
                onBlock = True
                onMap = False
                onPizza = False
                onPlat = False
                pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_ARROW)
                putTail = False
                x,y = [0,0]

            if event.key == pygame.K_p:
                for i in spizzas:print("pizza: ",i)
                for i in splatforms:print("plat: ",i)
                for i in sblocks:print("block: ",i)
            
            ####################### FINISH EDITING ##########################
            if event.key == pygame.K_ESCAPE or event.key == pygame.K_RETURN:
                f = open("map01.dat", 'w');
                f.close()
                f = open("map01.dat", 'a');
                for i in range(20):
                    for m in range(40):
                        if tiles[m][i].stat == None:
                            strr = '0'
                        else: strr = str(tiles[m][i].no)
                        f.write(strr)
                        if m!=39: f.write(" ")
                    f.write('\n')
                f.close()

                f = open("ents01.dat", 'w')
                f.close()
                f = open("ents01.dat", 'a')
                
                for pi in spizzas:
                    line = "PIZZA "
                    line += str(pi[0]) + " " + str(pi[1]) + '\n'
                    f.write(line)

                for pl in splatforms:
                    line = "PLATFORM "
                    line += str(pl[0]) + " " + str(pl[1]) + " " + str(pl[2]) + " " + str(pl[3]) + '\n'
                    f.write(line)

                for b in sblocks:
                    line = "BLOCK "
                    line += str(b[0]) + " " + str(b[1]) + '\n'
                    f.write(line)
                
                f.close()
                
                pygame.quit()
                os._exit(0)
            #################################################################
        if event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1: draw=True
            if event.button == 3: erase=True
            
        if event.type == pygame.MOUSEBUTTONUP:
            erase = False
            draw=False

        if (event.type == pygame.MOUSEMOTION) and wheeling:
            wheeling=False
            scr.fill((0,34,64))
            draw_board(n,nx)
            drawTiles()
            drawEnts()
            flip()

        ######################### TILE EDIT ######################
        if (event.type == pygame.MOUSEWHEEL) & onMap:
            wheeling = True
            if not onMapBg:
                tileNo = (tileNo-1+event.y)%15+1
                scr.fill((0,34,64))
                scr.blit(pygame.transform.scale(tileI[tileNo-1], (nx*2, nx*2)), (pygame.mouse.get_pos()[0]-nx,pygame.mouse.get_pos()[1]-nx))
            else:
                tileNo = (tileNo-1+event.y)%TOTALBGTILES+1
                scr.fill((0,34,64))
                scr.blit(pygame.transform.scale(tileBg[tileNo-1], (nx*2, nx*2)), (pygame.mouse.get_pos()[0]-nx,pygame.mouse.get_pos()[1]-nx))
            flip()
            
        if (event.type == pygame.MOUSEMOTION) & draw & onMap:
            x=event.pos[0]//nx
            y=event.pos[1]//nx
            if tiles[x][y].stat==None:
                tiles[x][y].stat="w"
                tiles[x][y].no=tileNo if not onMapBg else -1*tileNo #not onMapBg ? tileNo : -tileNo
                tiles[x][y].paint()
                drawEnts()
                flip()
                
        if (event.type == pygame.MOUSEMOTION) & erase & onMap:
            x=event.pos[0]//nx
            y=event.pos[1]//nx
            tiles[x][y].stat=None
            tiles[x][y].paint()
            drawEnts()
            flip()
        ##########################################################

        ######################### PIZZA EDIT ######################
        if (event.type == pygame.MOUSEBUTTONDOWN) & draw & onPizza:
            x=(event.pos[0]*2560)/(n*nx)
            y=(event.pos[1]*2560)/(n*nx)
            spizzas.append([x-15,y-15])
                    
            drawEnts()
            flip()
                
        if (event.type == pygame.MOUSEBUTTONDOWN) & erase & onPizza:
            x=event.pos[0]
            y=event.pos[1]
            for p in spizzas:
                if inrect(p[-1],x,y):
                    spizzas.remove(p)
                    scr.fill((0,34,64))
                    draw_board(n,nx)
                    drawTiles()
                    drawEnts()
                    flip()
        ##########################################################

        ######################### PLATFORM EDIT ######################
        if (event.type == pygame.MOUSEBUTTONDOWN) & draw & onPlat:
            if not putTail:
                x=(event.pos[0]*2560)/(n*nx)
                y=(event.pos[1]*2560)/(n*nx)
                pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_HAND)
                putTail = True
            else:
                xe=(event.pos[0]*2560)/(n*nx)
                ye=(event.pos[1]*2560)/(n*nx)
                pygame.mouse.set_cursor(pygame.SYSTEM_CURSOR_ARROW)#pygame.cursors.arrow)
                putTail = False
                splatforms.append([x-62,y-17,xe-62,ye-17])
                    
            drawEnts()
            flip()
                
        if (event.type == pygame.MOUSEBUTTONDOWN) & erase & onPlat:
            x=event.pos[0]
            y=event.pos[1]
            for p in splatforms:
                if inrect(p[-1],x,y):
                    splatforms.remove(p)
                    scr.fill((0,34,64))
                    draw_board(n,nx)
                    drawTiles()
                    drawEnts()
                    flip()
        ##########################################################

        ######################### BLOCK EDIT ######################
        if (event.type == pygame.MOUSEBUTTONDOWN) & draw & onBlock:
            x=(event.pos[0]*2560)/(n*nx)
            y=(event.pos[1]*2560)/(n*nx)
            sblocks.append([x-32,y-32])
                    
            drawEnts()
            flip()
                
        if (event.type == pygame.MOUSEBUTTONDOWN) & erase & onBlock:
            x=event.pos[0]
            y=event.pos[1]
            for b in sblocks:
                if inrect(b[-1],x,y):
                    sblocks.remove(b)
                    scr.fill((0,34,64))
                    draw_board(n,nx)
                    drawTiles()
                    drawEnts()
                    flip()
        ##########################################################
            
        if event.type == pygame.QUIT:
            pygame.quit()
            os._exit(1)
            
        sleep(0.01)

