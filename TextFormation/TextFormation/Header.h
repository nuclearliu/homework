//
//  Header.h
//  TextFormation
//
//  Created by 刘可立 on 2020/4/7.
//  Copyright © 2020 刘可立. All rights reserved.
//

#ifndef Header_h
#define Header_h

#define MAXSTRLEN 160
typedef unsigned char SString[MAXSTRLEN + 1];

int PageLen = 56, PageWed = 60, LeftMargin = 10, HeadingLen = 5, FootingLen = 5, StartPageNum = 1;
FILE * fp1;
FILE * fp2;
SString dir;

#endif /* Header_h */
