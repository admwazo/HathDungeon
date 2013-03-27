#ifndef _DungeonLevel_Included_
#define _DungeonLevel_Included_

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <map>

class DungeonLevel
{
    private:
        std::vector<std::vector<char>> vvTiles;
    	std::vector<DungeonLevel*> vSectors;
    	int iStartRow;
    	int iEndRow;
    	int iStartColumn;
    	int iEndColumn;
    	int iNumTiles;
    	//requirements
    	int iMinLength;	//minimum length of room (including wall tiles and invisible boundary) - set at 9
    	int iMinTiles;	//minimum number of tiles - set at 400
    	int iMinRooms; //minimum number of rooms - set at 5
		char cHoriWallTile; //'-'
    	char cVertiWallTile; //'|'
    	char cVacantTile; //' '
    	char cRoomTile; //'.'
		char cTunnelTile; //'#'
		char cUpTile; //'<'
		char cDownTile; //'>'
    	
    public:
        DungeonLevel(int iWidth, int iHeight);
        ~DungeonLevel();
		virtual int FindSector(int iRow, int iCol, std::vector<DungeonLevel*> vTestSects);
    	virtual void BuildRooms();
    	virtual bool SpawnSector(DungeonLevel* dlSector);
      	virtual void Display();
		virtual void DrawTunnels();
        virtual void SortSectors();
        virtual void SpawnElements();
		virtual void RandomPos(int & iCol, int & iRow, DungeonLevel* dlSector);
        virtual int GetTiles();
        virtual void SetTiles(int i);
        virtual char Get(int iRow, int iCol);
        virtual void Set(int iRow, int iCol, char cAvatar);
        virtual int GetWidth(int iRow);
        virtual int GetHeight();
		virtual int GetEndRow();
		virtual int GetStartRow();
		virtual int GetEndColumn();
		virtual int GetStartColumn();
        virtual std::vector<DungeonLevel*> GetVSectors();
};

#endif
