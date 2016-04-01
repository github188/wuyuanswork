//LIB_XML.H

/*##############################################################################
#工程描述:
#       创建和解析XML文件
#
#文件描述:
# 
#作者信息:
#       1215343312@qq.com                                   2012-05-25   创建
#版权信息:
#       Copyright(c) 2008~201x at TJ
#  	    1215343312@qq.com All rights reserved.
###############################################################################*/

#ifndef LIB_XML_H
#define LIB_XML_H
#ifdef WIN32
#if defined(LIB_XML_EXPORTS)
#define TJXML_API  extern "C" __declspec(dllexport) 
#else 
#define TJXML_API  extern "C" __declspec(dllimport) 
#endif
#else//LINUX
#define TJXML_API  //extern "C" 
#endif//WIN32


#ifndef HNODE   //结点
#define HNODE void *
#endif//HNODE

#ifndef HXMLFILE   //文档句柄
#define HXMLFILE void *
#endif//HXMLFILE

#ifndef HXMLELEMENT //节点元素
#define HXMLELEMENT void *
#endif//HXMLFILE

#ifndef HXMLTEXT    //节点文档
#define HXMLTEXT    void *
#endif//HXMLTEXT

#ifndef HXMLATTRB   //节点属性
#define HXMLATTRB   void *
#endif//HXMLATTRB

#ifndef CHAR 
#define CHAR  char
#endif//CHAR

#ifndef INT
#define INT  int
#endif//INT

#ifndef VOID
#define VOID void
#endif//VOID

#ifndef BOOL
#define BOOL int
#endif//BOOL

#ifndef TRUE
#define TRUE 1
#endif//TRUE

#ifndef FALSE
#define FALSE 0
#endif//FALSE

#ifndef FLOAT
#define FLOAT float
#endif//FLOAT

#ifndef USHORT
#define USHORT unsigned short
#endif//USHORT

#ifndef DOUBLE
#define DOUBLE double
#endif//DOUBLE


typedef enum{
	VALTYPE_CHAR    =  1,
	VALTYPE_INT     =  2,
	VALTYPE_FLOAT   =  3,
	VALTYPE_BOOL    =  4,
	VALTYPE_BOOLSTR =  5,
}ENU_VALUETYPE;

TJXML_API   HXMLFILE       XML_CreateFile             (CHAR *lpszFileName,CHAR*lpszRoot,BOOL  bIsRead);
TJXML_API   VOID           XML_CloseFile              (HXMLFILE hXmlFile);

TJXML_API   HXMLELEMENT    XML_GetRootElement         (HXMLFILE hXmlFile);
TJXML_API   HXMLELEMENT    XML_GetChildElement        (HXMLELEMENT Element);
TJXML_API   HXMLELEMENT    XML_GetNextElement         (HXMLELEMENT Element);
TJXML_API   HXMLELEMENT    XML_CreateElement          (HXMLFILE hXmlFile,HXMLELEMENT ParentElement,CHAR *lpszElement);
TJXML_API   HXMLELEMENT    XML_LinkElement            (HXMLELEMENT ParentElement,HXMLELEMENT hElement);

TJXML_API   HXMLATTRB      XML_ElementGetAttrb        (HXMLELEMENT hElement,CHAR** lpVal);
TJXML_API   BOOL           XML_ElementGetValue        (HXMLELEMENT hElement,CHAR *ElementName,VOID * lpVal,USHORT nValSize,ENU_VALUETYPE ValType);
TJXML_API   BOOL           XML_ElementSetValue        (HXMLELEMENT hElement,CHAR *ElementName,VOID * lpVal,USHORT nValSize,ENU_VALUETYPE ValType);
TJXML_API   CHAR*          XML_ElementGetLabel        (HXMLELEMENT hElement);

TJXML_API   HXMLTEXT       XML_CreateText             (HXMLFILE hXmlFile,HXMLELEMENT ParentElement,CHAR *lpszElement);
TJXML_API   HXMLTEXT       XML_LinkText               (HXMLELEMENT ParentElement,HXMLTEXT hText);
//                         XML_FirstChild(HXMLElement ,....);

/////////////////////////////////////////////////////////////////////////////////

//节点类TiXmlNode
TJXML_API const CHAR* XML_GetValue(HNODE hNode);//得到节点名hNode的值
TJXML_API VOID  XML_SetValue(HNODE hNode, const CHAR *pszValue);//设置节点名hNode的值为pszValue
TJXML_API VOID  XML_Clear(HNODE hNode);//删除本节点的所有子节点（包括子节点含的从子节点），但不修改本节点
TJXML_API HNODE XML_Parent(HNODE hNode);//得到父节点
//子节点
TJXML_API HNODE XML_FirstChild(HNODE hNode);//返回第一个子节点对象的指针
TJXML_API HNODE XML_FirstChildByValue(HNODE hNode, const CHAR *pszValue);
TJXML_API HNODE XML_LastChild(HNODE hNode);//返回最后一个子节点对象的指针
TJXML_API HNODE XML_LastChildByValue(HNODE hNode, const CHAR *pszValue);
//编辑子节点
TJXML_API HNODE XML_LinkEndChild(HNODE hNode, HNODE hAddThis);//插入新节点hAddThis到hNode后面
TJXML_API HNODE XML_InsertEndChild(HNODE hNode, const HNODE hAddThis);//插入新节点到末尾
TJXML_API HNODE XML_InsertBeforeChild(HNODE hNode, HNODE *phBeforeThis, const HNODE hAddThis);//在指定节点位置前插入新节点
TJXML_API HNODE XML_InsertAfterChild (HNODE hNode, HNODE *phAfterThis, const HNODE hAddThis);//在指定节点位置后插入新节点
TJXML_API HNODE XML_ReplaceChild(HNODE hNode, HNODE *phReplaceThis, const HNODE hWithThis);//替换指定的节点
TJXML_API BOOL  XML_RemoveChild(HNODE hNode, HNODE hRemoveThis);//删除指定的节点
//同级节点
TJXML_API HNODE XML_PreviousSibling(HNODE hNode);//根据当前节点，返回上一个节点的指针
TJXML_API HNODE XML_PreviousSiblingByValue(HNODE hNode, const CHAR *pszValue);
TJXML_API HNODE XML_NextSibling(HNODE hNode);//根据当前节点，返回下一个节点的指针
TJXML_API HNODE XML_NextSiblingByValue(HNODE hNode, const CHAR *pszValue);
//遍历元素
TJXML_API HNODE XML_NextSiblingElement(HNODE hNode);//返回下一个同级元素而忽略其他类型的节点
TJXML_API HNODE XML_NextSiblingElementByValue(HNODE hNode, const CHAR *pszValue);//返回下一个名为pszValue的同级元素
TJXML_API HNODE XML_FirstChildElement(HNODE hNode);//返回上一个同级元素而忽略其他类型的节点
TJXML_API HNODE XML_FirstChildElementByValue(HNODE hNode, const CHAR *pszValue);//返回下一个名为pszValue的子元素

TJXML_API BOOL  XML_NoChildren(HNODE hNode);//该节点没有子节点返回true

/////////////////////////////////////////////////////////////////////////////////
//XML文档类TiXmlDocument
TJXML_API HNODE XML_DocNew(VOID);//创建一个新文档
TJXML_API VOID  XML_DocDelete(HNODE hDoc);//删除文档
TJXML_API BOOL  XML_DocFromFile(HNODE hDoc, const CHAR *pszFileName);//载入xml文档
TJXML_API BOOL  XML_DocToFile(HNODE hDoc, const CHAR *pszFileName);//保存文档对象，保存为名为pszFileName的文件
TJXML_API const CHAR* XML_DocFromString(HNODE hDoc, const CHAR *pszString);//将字符串转换成文档
TJXML_API const CHAR* XML_DocToString(HNODE hDoc);//得到文档内容并返回字符串
TJXML_API HNODE XML_DocRootElement(HNODE hDoc);//得到文档根元素
TJXML_API BOOL  XML_DocError(HNODE hDoc);//如果文档出错返回true
TJXML_API VOID  XML_DocPrint(HNODE hDoc);//打印文档内容
//元素属性TiXmlElement
TJXML_API HNODE XML_ElementNew(const CHAR *pszValue);//增加一个名为pszValue新元素
TJXML_API HNODE XML_ElementWithStringNew(const CHAR *pszValue, const CHAR *pszText);//增加一个名为pszValue的（字符串值为pszText）新元素
TJXML_API HNODE XML_ElementWithIntNew(const CHAR *pszValue, int nText);//增加一个名为pszValue的（整型值为pszText）新元素
TJXML_API HNODE XML_ElementWithDoubleNew(const CHAR *pszValue, double dText);//增加一个名为pszValue的（浮点值为pszText）新元素
TJXML_API HNODE XML_ElementWithStrBoolNew(const CHAR *pszValue, BOOL bText);//增加一个名为pszValue的（真假值为pszText:=true?false）新元素
TJXML_API VOID  XML_ElementDelete(HNODE hElement);
TJXML_API const CHAR* XML_ElementGetStrAttribute(HNODE hElement, const CHAR *pszName);//得到节点元素hElement的字符串型值
TJXML_API int   XML_ElementGetIntAttribute(HNODE hElement, const CHAR *pszName);//得到节点元素hElement的整型值
TJXML_API BOOL  XML_ElementGetBoolAttribute(HNODE hElement, const CHAR *pszName);//得到节点元素hElement的真假型值
TJXML_API VOID  XML_ElementSetStrAttribute(HNODE hElement, const CHAR *pszName, const CHAR *pszValue);//设置节点元素hElement的字符串型值
TJXML_API VOID  XML_ElementSetIntAttribute(HNODE hElement, const CHAR *pszName, int nValue);//设置节点元素hElement的整型值
TJXML_API VOID  XML_ElementSetDoubleAttribute(HNODE hElement, const CHAR *pszName, double dValue);//设置节点元素hElement的浮点型值
TJXML_API VOID  XML_ElementSetStrBoolAttribute(HNODE hElement, const CHAR *pszName, BOOL bValue);//设置节点元素hElement的真假型值
TJXML_API VOID  XML_ElementRemoveAttribute(HNODE hElement, const CHAR *pszName);//删除指定名称的属性
TJXML_API const CHAR* XML_ElementGetText(HNODE hElement);
TJXML_API int   XML_ElementGetTextToInt(HNODE hElement);
TJXML_API BOOL  XML_ElementGetTextToBool(HNODE hElement);

TJXML_API HNODE XML_TextNew(const CHAR *pszValue);
TJXML_API VOID  XML_TextDelete(HNODE hText);
//注释类TiXmlComment
TJXML_API HNODE XML_CommentNew(const CHAR *pszValue);
TJXML_API VOID  XML_CommentDelete(HNODE hComment);
//声明类TiXmlDeclaration
TJXML_API HNODE XML_DeclarationNew(const CHAR *pszVersion, const CHAR *pszEncoding, const CHAR *pszStandalone);
TJXML_API VOID  XML_DeclarationDelete(HNODE hDeclaration);
/////////////////////////////////////////////////////////////////////////////////

#endif//LIB_XML_H

