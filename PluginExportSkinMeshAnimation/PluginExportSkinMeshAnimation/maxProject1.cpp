//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "maxProject1.h"
#include <conio.h>  
#include"MeshEnumProc.h"
#include <algorithm> 


#define maxProject1_CLASS_ID	Class_ID(0x8d231fbc, 0xae14656a)

class maxProject1 : public SceneExport {
public:
	//Constructor/Destructor
	maxProject1();
	~maxProject1();

	int				ExtCount();					// Number of extensions supported
	const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
	const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
	const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
	const TCHAR *	AuthorName();				// ASCII Author name
	const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	const TCHAR *	OtherMessage1();			// Other message #1
	const TCHAR *	OtherMessage2();			// Other message #2
	unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

	BOOL SupportsOptions(int ext, DWORD options);
	int  DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);
};



class maxProject1ClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new maxProject1(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return maxProject1_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("maxProject1"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle


};


ClassDesc2* GetmaxProject1Desc() { 
	static maxProject1ClassDesc maxProject1Desc;
	return &maxProject1Desc; 
}





INT_PTR CALLBACK maxProject1OptionsDlgProc(HWND hWnd,UINT message,WPARAM,LPARAM lParam) {
	static maxProject1* imp = nullptr;

	switch(message) {
	case WM_INITDIALOG:
		imp = (maxProject1 *)lParam;
		CenterWindow(hWnd,GetParent(hWnd));
		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return 1;
	}
	return 0;
}


//--- maxProject1 -------------------------------------------------------
maxProject1::maxProject1()
{

}

maxProject1::~maxProject1() 
{

}

int maxProject1::ExtCount()
{
	//#pragma message(TODO("Returns the number of file name extensions supported by the plug-in."))
	return 1;
}

const TCHAR *maxProject1::Ext(int /*i*/)
{		
	//#pragma message(TODO("Return the 'i-th' file name extension (i.e. \"3DS\")."))
	return _T("model");
}

const TCHAR *maxProject1::LongDesc()
{
	//#pragma message(TODO("Return long ASCII description (i.e. \"Targa 2.0 Image File\")"))
	return _T("lives2d anim model file");
}

const TCHAR *maxProject1::ShortDesc() 
{			
	//#pragma message(TODO("Return short ASCII description (i.e. \"Targa\")"))
	return _T("lives2d anim model file");
}

const TCHAR *maxProject1::AuthorName()
{			
	//#pragma message(TODO("Return ASCII Author name"))
	return _T("");
}

const TCHAR *maxProject1::CopyrightMessage() 
{	
	//#pragma message(TODO("Return ASCII Copyright message"))
	return _T("");
}

const TCHAR *maxProject1::OtherMessage1() 
{		
	//TODO: Return Other message #1 if any
	return _T("");
}

const TCHAR *maxProject1::OtherMessage2() 
{		
	//TODO: Return other message #2 in any
	return _T("");
}

unsigned int maxProject1::Version()
{				
	//#pragma message(TODO("Return Version number * 100 (i.e. v3.01 = 301)"))
	return 100;
}

void maxProject1::ShowAbout(HWND /*hWnd*/)
{			
	// Optional
}

BOOL maxProject1::SupportsOptions(int /*ext*/, DWORD /*options*/)
{
	//#pragma message(TODO("Decide which options to support.  Simply return true for each option supported by each Extension the exporter supports."))
	return TRUE;
}



std::string WChar2Ansi(LPCWSTR pwszSrc)  
{  
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);  

	if (nLen<= 0) return std::string("");  

	char* pszDst = new char[nLen];  
	if (NULL == pszDst) return std::string("");  

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);  
	pszDst[nLen -1] = 0;  

	std::string strTemp(pszDst);  
	delete [] pszDst;  

	return strTemp;  
}  

string ws2s(wstring& inputws){ return WChar2Ansi(inputws.c_str()); }  

//Converting a Ansi string to WChar string  

std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen)  

{  
	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);  
	if(nSize <= 0) return NULL;  

	WCHAR *pwszDst = new WCHAR[nSize+1];  
	if( NULL == pwszDst) return NULL;  

	MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);  
	pwszDst[nSize] = 0;  

	if( pwszDst[0] == 0xFEFF) // skip Oxfeff  
		for(int i = 0; i < nSize; i ++)   
			pwszDst[i] = pwszDst[i+1];  

	wstring wcharString(pwszDst);  
	delete pwszDst;  

	return wcharString;  
}  

std::wstring s2ws(const string& s){ return Ansi2WChar(s.c_str(),s.size());} 


//bool CreateExportPluginDialog(IGameScene* varGameScene,const string& varFileName);

int	maxProject1::DoExport(const TCHAR* name, ExpInterface* ei, Interface* ip, BOOL suppressPrompts, DWORD options)
{
	//#pragma message(TODO("Implement the actual file Export here and"))

	if(!suppressPrompts)
		DialogBoxParam(hInstance, 
		MAKEINTRESOURCE(IDD_PANEL), 
		GetActiveWindow(), 
		maxProject1OptionsDlgProc, (LPARAM)this);

	//#pragma message(TODO("return TRUE If the file is exported properly"))

	//AllocConsole();

	//_cprintf("Export Begin %s ",name);

	//MeshEnumProc tmpMeshEnumProc(name,ei->theScene,options);
	//const char* tmpName=(const char*)name;
	//std::wstring tmpName=std::wstring(name);
	//MeshEnumProc* tmpProc=new MeshEnumProc(tmpName,ei->theScene,ip,options);
	//ei->theScene->EnumTree(tmpProc);

	bool tmpSelected=(options & SCENE_EXPORT_SELECTED)?true:false;
	IGameScene* tmpGameScene=GetIGameInterface();

	IGameConversionManager* tmpGameConversionManager=GetConversionManager();
	tmpGameConversionManager->SetCoordSystem(IGameConversionManager::IGAME_OGL);

	tmpGameScene->InitialiseIGame(tmpSelected);

	tmpGameScene->SetStaticFrame(0);

	//窗口
	//CreateExportPluginDialog(tmpGameScene,name);


	int tmpMeshPart=0;

	//得到第一级
	int tmpTopLevelNodeCount=tmpGameScene->GetTopLevelNodeCount();
	if(tmpTopLevelNodeCount==0)
	{
		tmpGameScene->ReleaseIGame();
		return TRUE;
	}
	for (int i=0;i<tmpTopLevelNodeCount;i++)
	{
		IGameNode* tmpGameNode=tmpGameScene->GetTopLevelNode(i);

		IGameObject* tmpGameObject=tmpGameNode->GetIGameObject();

		IGameObject::ObjectTypes tmpObjectType=tmpGameObject->GetIGameType();

		if(IGameObject::IGAME_MESH==tmpObjectType)
		{
			tmpMeshPart++;
		}
	}
	if(tmpMeshPart==0)
	{
		return FALSE;
	}
	for (int i=0;i<tmpTopLevelNodeCount;i++)
	{
		vector<Vertex> tmpVectorVertex;
		vector<unsigned short> tmpVectorIndices;
		vector<glm::vec2> tmpVectorTexCoords;
		vector<Texture> tmpVectorTexture;
		int tmpTextureSize=0;

		vector<IGameNode*> tmpVectorGameNodeBones;
		vector<map<unsigned short,float>> tmpVectorWeight;

		vector<GMatrix> tmpVectorBoneGMatrixZeroFrame;
		vector<GMatrix> tmpVectorBoneGMatrixInvert;//存储第0帧逆矩阵
		map<TimeValue,vector<GMatrix>> tmpMapBoneGMatrix;//存储每一帧的矩阵

		map<IGameMaterial*,vector<int>> tmpMapMaterial;//存储材质与顶点的关系

		IGameNode* tmpGameNode=tmpGameScene->GetTopLevelNode(i);

		IGameObject* tmpGameObject=tmpGameNode->GetIGameObject();

		IGameObject::ObjectTypes tmpObjectType=tmpGameObject->GetIGameType();

		if(IGameObject::IGAME_MESH!=tmpObjectType)
		{
			continue;
		}

		IGameMesh* tmpGameMesh=(IGameMesh*)tmpGameObject;
		tmpGameMesh->GetMaxMesh()->buildNormals();

		if(!tmpGameMesh->InitializeData())
		{
			return FALSE;
		}

		int tmpVertexCount=tmpGameMesh->GetNumberOfVerts();
		for (int tmpVertexIndex=0;tmpVertexIndex<tmpVertexCount;tmpVertexIndex++)
		{
			Vertex tmpVertex;
			tmpVectorVertex.push_back(tmpVertex);
		}

		int tmpFaceCount=tmpGameMesh->GetNumberOfFaces();

		for (int tmpFaceIndex=0;tmpFaceIndex<tmpFaceCount;tmpFaceIndex++)
		{
			FaceEx* tmpFaceEx=tmpGameMesh->GetFace(tmpFaceIndex);

			for (int tmpFaceVertexIndex=0;tmpFaceVertexIndex<3;tmpFaceVertexIndex++)
			{
				//顶点
				Vertex tmpVertex;

				//坐标
				int tmpVertexIndex=tmpFaceEx->vert[tmpFaceVertexIndex];
				Point3 tmpPoint3Position=tmpGameMesh->GetVertex(tmpVertexIndex);
				glm::vec3 tmpPosition(tmpPoint3Position.x,tmpPoint3Position.y,tmpPoint3Position.z);
				tmpVertex.Position=tmpPosition;

				//Normal
				int tmpNormalIndex=tmpFaceEx->norm[tmpFaceVertexIndex];
				Point3 tmpPoint3Normal=tmpGameMesh->GetNormal(tmpNormalIndex);
				glm::vec3 tmpNormal=glm::vec3(tmpPoint3Normal.x,tmpPoint3Normal.y,tmpPoint3Normal.z);
				tmpVertex.Normal=tmpNormal;

				//纹理坐标
				int tmpTexCoordIndex=tmpFaceEx->texCoord[tmpFaceVertexIndex];
				Point2 tmpPoint2TexVertex= tmpGameMesh->GetTexVertex(tmpTexCoordIndex);
				glm::vec2 tmpTexCoord=glm::vec2(tmpPoint2TexVertex.x,tmpPoint2TexVertex.y);
				tmpVertex.TexCoords=tmpTexCoord;


				tmpVectorIndices.push_back(tmpVertexIndex);

				tmpVectorVertex[tmpVertexIndex]=tmpVertex;
			}

			//获取当前面的材质
			IGameMaterial* tmpGameMaterial=tmpGameMesh->GetMaterialFromFace(tmpFaceEx);
			if(tmpGameMaterial==NULL)
			{
				continue;
			}
			else
			{

				bool tmpFind=false;
				for (std::map<IGameMaterial*,vector<int>>::iterator tmpIterBegin=tmpMapMaterial.begin();tmpIterBegin!=tmpMapMaterial.end();tmpIterBegin++)
				{
					if(tmpIterBegin->first==tmpGameMaterial)
					{
						tmpFind=true;
						tmpIterBegin->second.push_back(tmpFaceEx->vert[0]);
						tmpIterBegin->second.push_back(tmpFaceEx->vert[1]);
						tmpIterBegin->second.push_back(tmpFaceEx->vert[2]);
						break;
					}
				}

				if(tmpFind==false)
				{
					vector<int> tmpVectorFaceIndex;
					tmpVectorFaceIndex.push_back(tmpFaceEx->vert[0]);
					tmpVectorFaceIndex.push_back(tmpFaceEx->vert[1]);
					tmpVectorFaceIndex.push_back(tmpFaceEx->vert[2]);
					tmpMapMaterial.insert(std::pair<IGameMaterial*,std::vector<int>>(tmpGameMaterial,tmpVectorFaceIndex));
				}
			}
		}

		//判断有没有修改器，有修改器的就是骨骼动画
		int tmpModifiersNum=tmpGameObject->GetNumModifiers();
		for (int tmpModifierIndex=0;tmpModifierIndex<tmpModifiersNum;tmpModifierIndex++)
		{
			IGameModifier* tmpGameModifier=tmpGameObject->GetIGameModifier(tmpModifierIndex);

			//只处理骨骼动画修改器
			if(tmpGameModifier->IsSkin())
			{
				TimeValue tmpTimeValueBegin=tmpGameScene->GetSceneStartTime();
				TimeValue tmpTimeValueEnd=tmpGameScene->GetSceneEndTime();
				TimeValue tmpTimeValueTicks=tmpGameScene->GetSceneTicks();

				IGameSkin* tmpGameSkin=(IGameSkin*)tmpGameModifier;
				int tmpNumOfSkinnedVerts=tmpGameSkin->GetNumOfSkinnedVerts();

				//获取顶点受骨骼影响数
				for (int tmpVertexIndex=0;tmpVertexIndex<tmpVectorVertex.size();tmpVertexIndex++)
				{
					int tmpNumberOfBoneOnVertex=tmpGameSkin->GetNumberOfBones(tmpVertexIndex);


					map<unsigned short,float> tmpMapWeightOneVertex;
					for (int tmpBoneIndexOnVertex=0;tmpBoneIndexOnVertex<tmpNumberOfBoneOnVertex;tmpBoneIndexOnVertex++)
					{
						//获取当前顶点的骨骼
						IGameNode* tmpGameNodeBone=tmpGameSkin->GetIGameBone(tmpVertexIndex,tmpBoneIndexOnVertex);
						if(tmpGameNodeBone==nullptr)
						{
							continue;
						}
						bool tmpContais=false;
						int tmpGameNodeBoneIndex=0;
						for (tmpGameNodeBoneIndex=0;tmpGameNodeBoneIndex<tmpVectorGameNodeBones.size();tmpGameNodeBoneIndex++)
						{
							if (tmpVectorGameNodeBones[tmpGameNodeBoneIndex]==tmpGameNodeBone)
							{
								tmpContais=true;
								break;
							}
						}
						if(tmpContais==false)
						{
							tmpVectorGameNodeBones.push_back(tmpGameNodeBone);
						}


						float tmpWeight=tmpGameSkin->GetWeight(tmpVertexIndex,tmpBoneIndexOnVertex);

						tmpMapWeightOneVertex.insert(pair<unsigned short,float>((unsigned short)tmpGameNodeBoneIndex,tmpWeight));
					}

					tmpVectorWeight.push_back(tmpMapWeightOneVertex);
				}

				//获取第0帧骨骼逆矩阵
				for (int tmpGameNodeBoneIndex=0;tmpGameNodeBoneIndex<tmpVectorGameNodeBones.size();tmpGameNodeBoneIndex++)
				{
					INode* tmpNodeBone=tmpVectorGameNodeBones[tmpGameNodeBoneIndex]->GetMaxNode();
					Matrix3 tmpMatrix3NodeBone=tmpNodeBone->GetObjTMAfterWSM(0);

					tmpVectorBoneGMatrixZeroFrame.push_back(tmpMatrix3NodeBone);

					tmpMatrix3NodeBone.Invert();
					//GMatrix tmpGMatrixNodeBone(tmpMatrix3NodeBone);
					GMatrix tmpGMatrixNodeBoneInvert(tmpMatrix3NodeBone);

					tmpVectorBoneGMatrixInvert.push_back(tmpGMatrixNodeBoneInvert);

					//test
					//Matrix3 tmpTestMatrix3=tmpNodeBone->GetObjTMAfterWSM(0) * tmpMatrix3NodeBone;

					GMatrix tmpGMatrixNodeBoneTest(tmpMatrix3NodeBone);
					GMatrix tmpTest=tmpGMatrixNodeBoneTest*tmpGMatrixNodeBoneInvert;

					int a=0;
				}

				//获取骨骼矩阵
				for (;tmpTimeValueBegin<=tmpTimeValueEnd;tmpTimeValueBegin+=tmpTimeValueTicks)
				{
					vector<GMatrix> tmpVectorBoneGMatrix;
					for (int tmpGameNodeBoneIndex=0;tmpGameNodeBoneIndex<tmpVectorGameNodeBones.size();tmpGameNodeBoneIndex++)
					{
						INode* tmpNodeBone=tmpVectorGameNodeBones[tmpGameNodeBoneIndex]->GetMaxNode();
						Matrix3 tmpMatrix3NodeBone=tmpNodeBone->GetObjTMAfterWSM(tmpTimeValueBegin);
						GMatrix tmpGMatrixNodeBone(tmpMatrix3NodeBone);

						tmpVectorBoneGMatrix.push_back(tmpGMatrixNodeBone);
					}

					tmpMapBoneGMatrix.insert(pair<TimeValue,vector<GMatrix>>(tmpTimeValueBegin,tmpVectorBoneGMatrix));
				}

			}
		}

		//获取子节点
		int tmpChildNodeCount=tmpGameNode->GetChildCount();
		for (int tmpChildNodeIndex=0;tmpChildNodeIndex<tmpChildNodeCount;tmpChildNodeIndex++)
		{
			IGameNode* tmpGameNodeChild=tmpGameNode->GetNodeChild(tmpChildNodeIndex);
			if(tmpGameNodeChild->IsTarget())
			{
				continue;
			}

		}


		//拆分mesh和anim文件
		wstring tmpExportFullPath(name);
		std::size_t tmpFind= tmpExportFullPath.find_last_of(L".");

		
		
		string tmpExportMeshPath;
		string tmpExportAnimPath;
		if(tmpMeshPart==1)
		{
			 tmpExportMeshPath= ws2s(tmpExportFullPath.substr(0,tmpFind)+L".mesh");
			 tmpExportAnimPath= ws2s(tmpExportFullPath.substr(0,tmpFind)+L".anim");

		}
		else
		{
			char tmpMeshFilePath[100];
			char tmpAnimFilePath[100];
			tmpExportMeshPath= ws2s(tmpExportFullPath.substr(0,tmpFind)+L"_%d.mesh");
			tmpExportAnimPath= ws2s(tmpExportFullPath.substr(0,tmpFind)+L"_%d.anim");

			sprintf(tmpMeshFilePath,tmpExportMeshPath.c_str(),i);
			tmpExportMeshPath=tmpMeshFilePath;
			
			sprintf(tmpAnimFilePath,tmpExportAnimPath.c_str(),i);
			tmpExportAnimPath=tmpAnimFilePath;
		}


		//写文件
		ofstream tmpOfStreamMesh(tmpExportMeshPath, ios::binary);
		ofstream tmpOfStreamAnim(tmpExportAnimPath,ios::binary);

		char tmpLogFilePath[20];
		sprintf(tmpLogFilePath,"c://log_%d.txt",i);
		ofstream foutLog(tmpLogFilePath);

		char tmpLogMaterialFilePath[100];
		sprintf(tmpLogMaterialFilePath,"c://log_material_%d.txt",i);
		ofstream foutLogMaterial(tmpLogMaterialFilePath);

		//写入mesh count;
		int meshcount = 1;
		tmpOfStreamMesh.write((char*)(&meshcount), sizeof(meshcount));

		std::cout << "MeshCount: " << meshcount << std::endl;
		foutLog<< "MeshCount: " << meshcount << endl;

		for (size_t meshindex = 0; meshindex < 1; meshindex++)
		{
			std::cout << "Mesh" << meshindex << std::endl;


			std::cout << "VertexCount:" << tmpVectorVertex.size() << std::endl;
			std::cout << "IndicesCount:" << tmpVectorIndices.size() << std::endl;
			std::cout << "TextureCount:" << tmpTextureSize << std::endl;

			foutLog << "VertexCount:" << tmpVectorVertex.size() << endl;
			foutLog << "IndicesCount:" << tmpVectorIndices.size() << endl;
			foutLog << "TextureCount:" <<tmpTextureSize << endl;

			int vertexsize =sizeof(Vertex) * tmpVectorVertex.size();

			int indicessize = sizeof(unsigned short)* tmpVectorIndices.size();

			int texturesize = (sizeof(Texture))* tmpTextureSize;


			//写入vertexsize;
			tmpOfStreamMesh.write((char*)(&vertexsize), sizeof(vertexsize));

			//写入vertex数据;
			for (size_t vertexindex = 0; vertexindex < tmpVectorVertex.size(); vertexindex++)
			{
				tmpOfStreamMesh.write((char*)(&tmpVectorVertex[vertexindex]), sizeof(tmpVectorVertex[vertexindex]));
			}

			foutLog << "Vertex:" << tmpVectorVertex.size()<< std::endl;
			for (size_t vertexindex = 0; vertexindex < tmpVectorVertex.size(); vertexindex++)
			{
				foutLog << "(" << tmpVectorVertex[vertexindex].Position.x << "," << tmpVectorVertex[vertexindex].Position.y << "," << tmpVectorVertex[vertexindex].Position.z << ")"<< std::endl;
			}

			foutLog << "UV:" << tmpVectorVertex.size()<< std::endl;
			for (size_t vertexindex = 0; vertexindex < tmpVectorVertex.size(); vertexindex++)
			{
				foutLog << "(" << tmpVectorVertex[vertexindex].TexCoords.x << "," << tmpVectorVertex[vertexindex].TexCoords.y << ")" << endl;
			}

			foutLog << "Normal:" <<tmpVectorVertex.size()<< std::endl;
			for (size_t vertexindex = 0; vertexindex < tmpVectorVertex.size(); vertexindex++)
			{
				foutLog << "(" << tmpVectorVertex[vertexindex].Normal.x << "," << tmpVectorVertex[vertexindex].Normal.y << "," << tmpVectorVertex[vertexindex].Normal.z << ")" << endl;
			}


			//写入indicessize;
			tmpOfStreamMesh.write((char*)(&indicessize), sizeof(indicessize));



			//写入indicess数据;
			for (size_t indexindex = 0; indexindex < tmpVectorIndices.size(); indexindex++)
			{
				tmpOfStreamMesh.write((char*)(&tmpVectorIndices[indexindex]), sizeof(tmpVectorIndices[indexindex]));
			}


			foutLog << "Indices:" << tmpVectorIndices.size()<< std::endl;
			for (size_t tmpIndicesIndex = 0; tmpIndicesIndex < tmpVectorIndices.size();)
			{
				int tmpIndex0=tmpIndicesIndex++;
				int tmpIndex1=tmpIndicesIndex++;
				int tmpIndex2=tmpIndicesIndex++;
				foutLog <<tmpVectorIndices[tmpIndex0] << "," << tmpVectorIndices[tmpIndex1] << "," << tmpVectorIndices[tmpIndex2] << endl;
			}


			//写入texturesize;
			tmpOfStreamMesh.write((char*)(&texturesize), sizeof(texturesize));

			//写入texture数据;
			for (size_t textureindex = 0; textureindex < texturesize; textureindex++)
			{
				//fout.write((char*)(&mesh.textures[textureindex]), sizeof(mesh.textures[textureindex]));
			}




			//Materials
			foutLogMaterial<<"Materials:"<<endl;

			int tmpMaterialCount=tmpMapMaterial.size();
			tmpOfStreamMesh.write((char*)(&tmpMaterialCount), sizeof(tmpMaterialCount));

			for (std::map<IGameMaterial*,vector<int>>::iterator tmpIterBegin=tmpMapMaterial.begin();tmpIterBegin!=tmpMapMaterial.end();tmpIterBegin++)
			{
				IGameMaterial* tmpGameMaterial=tmpIterBegin->first;
				string tmpMaterialName=WChar2Ansi( tmpGameMaterial->GetMaterialName());

				foutLogMaterial<<tmpMaterialName<<endl;

				unsigned char tmpMaterialNameSize=tmpMaterialName.size()+1;
				tmpOfStreamMesh.write((char*)(&tmpMaterialNameSize), sizeof(tmpMaterialNameSize));
				tmpOfStreamMesh.write((char*)(tmpMaterialName.c_str()), tmpMaterialNameSize);

				unsigned char tmpNumberOfTextureMaps = tmpGameMaterial->GetNumberOfTextureMaps();		//how many texture of the material
				foutLogMaterial<<"Texture Count:"<<(int)tmpNumberOfTextureMaps<<endl;
				tmpOfStreamMesh.write((char*)(&tmpNumberOfTextureMaps), sizeof(tmpNumberOfTextureMaps));

				for (int tmpTextureMapIndex=0;tmpTextureMapIndex<tmpNumberOfTextureMaps;tmpTextureMapIndex++)
				{
					IGameTextureMap* tmpGameTextureMap=tmpGameMaterial->GetIGameTextureMap(tmpTextureMapIndex);
					if(tmpGameTextureMap!=NULL)
					{
						//文件路径						
						string tmpBitmapPath= WChar2Ansi( tmpGameTextureMap->GetBitmapFileName());
						foutLogMaterial<<"Texture BitmapPath:"<<tmpBitmapPath<<endl;

						//拷贝图片到导出目录
						wstring tmpBitmapPathW=tmpGameTextureMap->GetBitmapFileName();
						wstring tmpBitmapNameW=tmpBitmapPathW.substr(tmpBitmapPathW.find_last_of('\\')+1);
						wstring tmpBitmapExportPathW=tmpExportFullPath.substr(0,tmpExportFullPath.find_last_of(L"\\")+1)+tmpBitmapNameW;
						CopyFile(tmpGameTextureMap->GetBitmapFileName(),tmpBitmapExportPathW.c_str(),FALSE);

						//文件名
						int tmpLastCharPosition = tmpBitmapPath.find_last_of('\\');
						string tmpBitmapName(tmpBitmapPath.substr(tmpLastCharPosition + 1) );
						unsigned char tmpBitmapNameSize=tmpBitmapName.size()+1;
						tmpOfStreamMesh.write((char*)(&tmpBitmapNameSize), sizeof(tmpBitmapNameSize));
						tmpOfStreamMesh.write((char*)(tmpBitmapName.c_str()), tmpBitmapNameSize);

						//获取UV的Tilling和Offset值
						IGameUVGen* tmpGameUVGen=tmpGameTextureMap->GetIGameUVGen();
						std::string tmpTextureClass=WChar2Ansi(tmpGameTextureMap->GetTextureClass());
						transform(tmpTextureClass.begin(),tmpTextureClass.end(),tmpTextureClass.begin(),toupper);

						if(strcmp(tmpTextureClass.c_str(),"BITMAP")!=0)
						{
							continue;
						}

						IGameProperty* tmpGamePropertyUTiling=tmpGameUVGen->GetUTilingData();
						float tmpUTilingValue=0.0f;
						if(tmpGamePropertyUTiling->GetPropertyValue(tmpUTilingValue))
						{
							tmpOfStreamMesh.write((char*)(&tmpUTilingValue), sizeof(tmpUTilingValue));
						}

						IGameProperty* tmpGamePropertyVTiling=tmpGameUVGen->GetVTilingData();
						float tmpVTilingValue=0.0f;
						if(tmpGamePropertyVTiling->GetPropertyValue(tmpVTilingValue))
						{
							tmpOfStreamMesh.write((char*)(&tmpVTilingValue), sizeof(tmpVTilingValue));
						}

						IGameProperty* tmpGamePropertyUOffset=tmpGameUVGen->GetUOffsetData();
						float tmpUOffsetValue=0.0f;
						if(tmpGamePropertyUOffset->GetPropertyValue(tmpUOffsetValue))
						{
							tmpOfStreamMesh.write((char*)(&tmpUOffsetValue), sizeof(tmpUOffsetValue));
						}

						IGameProperty* tmpGamePropertyVOffset=tmpGameUVGen->GetVOffsetData();
						float tmpVOffsetValue=0.0f;
						if(tmpGamePropertyVOffset->GetPropertyValue(tmpVOffsetValue))
						{
							tmpOfStreamMesh.write((char*)(&tmpVOffsetValue), sizeof(tmpVOffsetValue));
						}

					}
				}

				std::vector<int> tmpVectorVertexIndex;
				for (size_t tmpVectorVertexInMaterialIndex=0;tmpVectorVertexInMaterialIndex<tmpIterBegin->second.size();tmpVectorVertexInMaterialIndex++)
				{
					/*bool tmpFind=false;
					for (size_t tmpVectorIndex=0;tmpVectorIndex<tmpVectorVertexIndex.size();tmpVectorIndex++)
					{
					if(tmpVectorVertexIndex[tmpVectorIndex]==tmpIterBegin->second[tmpVectorVertexInMaterialIndex])
					{
					tmpFind=true;
					break;
					}
					}

					if(tmpFind==false)*/
					{
						tmpVectorVertexIndex.push_back(tmpIterBegin->second[tmpVectorVertexInMaterialIndex]);
					}
				}

				int tmpVertexSizeInMaterial=tmpVectorVertexIndex.size();
				tmpOfStreamMesh.write((char*)(&tmpVertexSizeInMaterial), sizeof(tmpVertexSizeInMaterial));

				for (size_t tmpVectorIndex=0;tmpVectorIndex<tmpVectorVertexIndex.size();tmpVectorIndex++)
				{
					int tmpVertexIndex= tmpVectorVertexIndex[tmpVectorIndex];
					tmpOfStreamMesh.write((char*)(&tmpVertexIndex), sizeof(tmpVertexIndex));
				}
			}

			//-----------------------------------------------------------------------------------------------------------------


			//写入骨骼数据
			TimeValue tmpTimeValueBegin=tmpGameScene->GetSceneStartTime();
			TimeValue tmpTimeValueEnd=tmpGameScene->GetSceneEndTime();
			TimeValue tmpTimeValueTicks=tmpGameScene->GetSceneTicks();
			int tmpFrameCount=(tmpTimeValueEnd-tmpTimeValueBegin)/tmpTimeValueTicks;
			tmpFrameCount=tmpFrameCount+1;
			tmpOfStreamAnim.write((char*)(&tmpFrameCount),sizeof(tmpFrameCount));

			tmpOfStreamAnim.write((char*)(&tmpTimeValueTicks),sizeof(tmpTimeValueTicks));


			int tmpGameNodeBoneSize=tmpVectorGameNodeBones.size();
			tmpOfStreamAnim.write((char*)(&tmpGameNodeBoneSize),sizeof(tmpGameNodeBoneSize));

			for (size_t tmpGameNodeBoneIndex=0;tmpGameNodeBoneIndex<tmpVectorGameNodeBones.size();tmpGameNodeBoneIndex++)
			{
				const wchar_t* tmpGameNodeBoneName=tmpVectorGameNodeBones[tmpGameNodeBoneIndex]->GetName();
				std::wstring tmpGameNodeBoneNameWString(tmpGameNodeBoneName);
				std::string tmpGameNodeBoneNameString=ws2s(tmpGameNodeBoneNameWString);
				foutLog<<tmpGameNodeBoneNameString<<std::endl;

				int tmpGameNodeBoneNameStringSize=tmpGameNodeBoneNameString.size()+1;
				tmpOfStreamAnim.write((char*)(&tmpGameNodeBoneNameStringSize),sizeof(tmpGameNodeBoneNameStringSize));
				tmpOfStreamAnim.write(tmpGameNodeBoneNameString.c_str(),tmpGameNodeBoneNameStringSize);
			}

			//Log输出第0帧矩阵
			foutLog<<"Zero Frame GMatrix:"<<endl;
			for (size_t tmpBoneGMatrixZeroFrameIndex=0;tmpBoneGMatrixZeroFrameIndex<tmpVectorBoneGMatrixZeroFrame.size();tmpBoneGMatrixZeroFrameIndex++)
			{
				const wchar_t* tmpGameNodeBoneName=tmpVectorGameNodeBones[tmpBoneGMatrixZeroFrameIndex]->GetName();
				std::wstring tmpGameNodeBoneNameWString(tmpGameNodeBoneName);
				std::string tmpGameNodeBoneNameString=ws2s(tmpGameNodeBoneNameWString);
				foutLog<<tmpGameNodeBoneNameString<<endl;

				GMatrix tmpBoneGMatrixZeroFrame=tmpVectorBoneGMatrixZeroFrame[tmpBoneGMatrixZeroFrameIndex];
				foutLog<<tmpBoneGMatrixZeroFrame[0][0]<<" "<<tmpBoneGMatrixZeroFrame[0][1]<<" "<<tmpBoneGMatrixZeroFrame[0][2]<<" "<<tmpBoneGMatrixZeroFrame[0][3]<<endl;
				foutLog<<tmpBoneGMatrixZeroFrame[1][0]<<" "<<tmpBoneGMatrixZeroFrame[1][1]<<" "<<tmpBoneGMatrixZeroFrame[1][2]<<" "<<tmpBoneGMatrixZeroFrame[1][3]<<endl;
				foutLog<<tmpBoneGMatrixZeroFrame[2][0]<<" "<<tmpBoneGMatrixZeroFrame[2][1]<<" "<<tmpBoneGMatrixZeroFrame[2][2]<<" "<<tmpBoneGMatrixZeroFrame[2][3]<<endl;
				foutLog<<tmpBoneGMatrixZeroFrame[3][0]<<" "<<tmpBoneGMatrixZeroFrame[3][1]<<" "<<tmpBoneGMatrixZeroFrame[3][2]<<" "<<tmpBoneGMatrixZeroFrame[3][3]<<endl;
			}

			//写入第0帧逆矩阵
			int tmpVectorBoneGMatrixInvertSize=tmpVectorBoneGMatrixInvert.size();
			tmpOfStreamAnim.write((char*)(&tmpVectorBoneGMatrixInvertSize),sizeof(tmpVectorBoneGMatrixInvertSize));

			foutLog<<"Invert GMatrix:"<<endl;
			for (size_t tmpBoneGMatrixInvertIndex=0;tmpBoneGMatrixInvertIndex<tmpVectorBoneGMatrixInvert.size();tmpBoneGMatrixInvertIndex++)
			{
				const wchar_t* tmpGameNodeBoneName=tmpVectorGameNodeBones[tmpBoneGMatrixInvertIndex]->GetName();
				std::wstring tmpGameNodeBoneNameWString(tmpGameNodeBoneName);
				std::string tmpGameNodeBoneNameString=ws2s(tmpGameNodeBoneNameWString);
				foutLog<<tmpGameNodeBoneNameString<<endl;

				GMatrix tmpBoneGMatrixInvert=tmpVectorBoneGMatrixInvert[tmpBoneGMatrixInvertIndex];
				foutLog<<tmpBoneGMatrixInvert[0][0]<<" "<<tmpBoneGMatrixInvert[0][1]<<" "<<tmpBoneGMatrixInvert[0][2]<<" "<<tmpBoneGMatrixInvert[0][3]<<endl;
				foutLog<<tmpBoneGMatrixInvert[1][0]<<" "<<tmpBoneGMatrixInvert[1][1]<<" "<<tmpBoneGMatrixInvert[1][2]<<" "<<tmpBoneGMatrixInvert[1][3]<<endl;
				foutLog<<tmpBoneGMatrixInvert[2][0]<<" "<<tmpBoneGMatrixInvert[2][1]<<" "<<tmpBoneGMatrixInvert[2][2]<<" "<<tmpBoneGMatrixInvert[2][3]<<endl;
				foutLog<<tmpBoneGMatrixInvert[3][0]<<" "<<tmpBoneGMatrixInvert[3][1]<<" "<<tmpBoneGMatrixInvert[3][2]<<" "<<tmpBoneGMatrixInvert[3][3]<<endl;

				glm::mat4x4 tmpMat4x4BoneGMatrixInvert;
				tmpMat4x4BoneGMatrixInvert[0][0]=tmpBoneGMatrixInvert[0][0];tmpMat4x4BoneGMatrixInvert[0][1]=tmpBoneGMatrixInvert[0][1];tmpMat4x4BoneGMatrixInvert[0][2]=tmpBoneGMatrixInvert[0][2];tmpMat4x4BoneGMatrixInvert[0][3]=tmpBoneGMatrixInvert[0][3];
				tmpMat4x4BoneGMatrixInvert[1][0]=tmpBoneGMatrixInvert[1][0];tmpMat4x4BoneGMatrixInvert[1][1]=tmpBoneGMatrixInvert[1][1];tmpMat4x4BoneGMatrixInvert[1][2]=tmpBoneGMatrixInvert[1][2];tmpMat4x4BoneGMatrixInvert[1][3]=tmpBoneGMatrixInvert[1][3];
				tmpMat4x4BoneGMatrixInvert[2][0]=tmpBoneGMatrixInvert[2][0];tmpMat4x4BoneGMatrixInvert[2][1]=tmpBoneGMatrixInvert[2][1];tmpMat4x4BoneGMatrixInvert[2][2]=tmpBoneGMatrixInvert[2][2];tmpMat4x4BoneGMatrixInvert[2][3]=tmpBoneGMatrixInvert[2][3];
				tmpMat4x4BoneGMatrixInvert[3][0]=tmpBoneGMatrixInvert[3][0];tmpMat4x4BoneGMatrixInvert[3][1]=tmpBoneGMatrixInvert[3][1];tmpMat4x4BoneGMatrixInvert[3][2]=tmpBoneGMatrixInvert[3][2];tmpMat4x4BoneGMatrixInvert[3][3]=tmpBoneGMatrixInvert[3][3];

				tmpOfStreamAnim.write((char*)(&tmpMat4x4BoneGMatrixInvert),sizeof(tmpMat4x4BoneGMatrixInvert));
			}

			//写入骨骼时间轴矩阵
			int tmpMapBoneGMatrixSize=tmpMapBoneGMatrix.size();
			tmpOfStreamAnim.write((char*)(&tmpMapBoneGMatrixSize),sizeof(tmpMapBoneGMatrixSize));

			foutLog<<"Animation:"<<std::endl;
			for (map<TimeValue,vector<GMatrix>>::iterator tmpIterBegin=tmpMapBoneGMatrix.begin();tmpIterBegin!=tmpMapBoneGMatrix.end();tmpIterBegin++)
			{
				TimeValue tmpTimeValueCurrent=tmpIterBegin->first;
				foutLog<<tmpTimeValueCurrent<<std::endl;

				tmpOfStreamAnim.write((char*)(&tmpTimeValueCurrent),sizeof(tmpTimeValueCurrent));

				vector<GMatrix> tmpVectorGMatrixCurrent=tmpIterBegin->second;

				int tmpVectorGMatrixCurrentSize=tmpVectorGMatrixCurrent.size();
				tmpOfStreamAnim.write((char*)(&tmpVectorGMatrixCurrentSize),sizeof(tmpVectorGMatrixCurrentSize));

				for (size_t tmpVectorGMatrixCurrentIndex=0;tmpVectorGMatrixCurrentIndex<tmpVectorGMatrixCurrent.size();tmpVectorGMatrixCurrentIndex++)
				{
					const wchar_t* tmpGameNodeBoneName=tmpVectorGameNodeBones[tmpVectorGMatrixCurrentIndex]->GetName();
					std::wstring tmpGameNodeBoneNameWString(tmpGameNodeBoneName);
					std::string tmpGameNodeBoneNameString=ws2s(tmpGameNodeBoneNameWString);
					foutLog<<tmpGameNodeBoneNameString<<endl;

					GMatrix tmpGMatrixNodeBone=tmpVectorGMatrixCurrent[tmpVectorGMatrixCurrentIndex];
					foutLog<<tmpGMatrixNodeBone[0][0]<<" "<<tmpGMatrixNodeBone[0][1]<<" "<<tmpGMatrixNodeBone[0][2]<<" "<<tmpGMatrixNodeBone[0][3]<<endl;
					foutLog<<tmpGMatrixNodeBone[1][0]<<" "<<tmpGMatrixNodeBone[1][1]<<" "<<tmpGMatrixNodeBone[1][2]<<" "<<tmpGMatrixNodeBone[1][3]<<endl;
					foutLog<<tmpGMatrixNodeBone[2][0]<<" "<<tmpGMatrixNodeBone[2][1]<<" "<<tmpGMatrixNodeBone[2][2]<<" "<<tmpGMatrixNodeBone[2][3]<<endl;
					foutLog<<tmpGMatrixNodeBone[3][0]<<" "<<tmpGMatrixNodeBone[3][1]<<" "<<tmpGMatrixNodeBone[3][2]<<" "<<tmpGMatrixNodeBone[3][3]<<endl;

					glm::mat4x4 tmpMat4x4BoneGMatrix;
					tmpMat4x4BoneGMatrix[0][0]=tmpGMatrixNodeBone[0][0];tmpMat4x4BoneGMatrix[0][1]=tmpGMatrixNodeBone[0][1];tmpMat4x4BoneGMatrix[0][2]=tmpGMatrixNodeBone[0][2];tmpMat4x4BoneGMatrix[0][3]=tmpGMatrixNodeBone[0][3];
					tmpMat4x4BoneGMatrix[1][0]=tmpGMatrixNodeBone[1][0];tmpMat4x4BoneGMatrix[1][1]=tmpGMatrixNodeBone[1][1];tmpMat4x4BoneGMatrix[1][2]=tmpGMatrixNodeBone[1][2];tmpMat4x4BoneGMatrix[1][3]=tmpGMatrixNodeBone[1][3];
					tmpMat4x4BoneGMatrix[2][0]=tmpGMatrixNodeBone[2][0];tmpMat4x4BoneGMatrix[2][1]=tmpGMatrixNodeBone[2][1];tmpMat4x4BoneGMatrix[2][2]=tmpGMatrixNodeBone[2][2];tmpMat4x4BoneGMatrix[2][3]=tmpGMatrixNodeBone[2][3];
					tmpMat4x4BoneGMatrix[3][0]=tmpGMatrixNodeBone[3][0];tmpMat4x4BoneGMatrix[3][1]=tmpGMatrixNodeBone[3][1];tmpMat4x4BoneGMatrix[3][2]=tmpGMatrixNodeBone[3][2];tmpMat4x4BoneGMatrix[3][3]=tmpGMatrixNodeBone[3][3];

					tmpOfStreamAnim.write((char*)(&tmpMat4x4BoneGMatrix),sizeof(tmpMat4x4BoneGMatrix));
				}
			}

			//顶点权重信息
			int tmpVectorVertexSize=tmpVectorVertex.size();
			tmpOfStreamAnim.write((char*)(&tmpVectorVertexSize),sizeof(tmpVectorVertexSize));

			for (size_t vertexindex = 0; vertexindex < tmpVectorWeight.size(); vertexindex++)
			{
				foutLog << "(" << tmpVectorVertex[vertexindex].Position.x << "," << tmpVectorVertex[vertexindex].Position.y << "," << tmpVectorVertex[vertexindex].Position.z << ")";

				map<unsigned short,float> tmpMapWeightOneVertex=tmpVectorWeight[vertexindex];

				int tmpMapWeightOneVertexSize=tmpMapWeightOneVertex.size();
				tmpOfStreamAnim.write((char*)(&tmpMapWeightOneVertexSize),sizeof(tmpMapWeightOneVertexSize));

				for (map<unsigned short,float>::iterator tmpIterBegin=tmpMapWeightOneVertex.begin();tmpIterBegin!=tmpMapWeightOneVertex.end();tmpIterBegin++)
				{
					foutLog<<" "<<tmpIterBegin->first<<":"<<tmpIterBegin->second;

					tmpOfStreamAnim.write((char*)(&tmpIterBegin->first),sizeof(tmpIterBegin->first));
					tmpOfStreamAnim.write((char*)(&tmpIterBegin->second),sizeof(tmpIterBegin->second));
				}
				foutLog<<endl;
			}


			//计算顶点初始位置 并存储
			foutLog<<"Write Vertex Position No Bone"<<endl;
			for (size_t vertexindex = 0; vertexindex < tmpVectorWeight.size(); vertexindex++)
			{
				map<unsigned short,float> tmpMapWeightOneVertex=tmpVectorWeight[vertexindex];

				//写入当前顶点受影响的骨骼数
				unsigned short tmpMapWeightOneVertexSize=tmpMapWeightOneVertex.size();
				tmpOfStreamAnim.write((char*)(&tmpMapWeightOneVertexSize),sizeof(tmpMapWeightOneVertexSize));

				std::vector<glm::vec3> tmpVectorOneVertexPositionNoBone;
				for (map<unsigned short,float>::iterator tmpIterBegin=tmpMapWeightOneVertex.begin();tmpIterBegin!=tmpMapWeightOneVertex.end();tmpIterBegin++)
				{
					GMatrix tmpBoneGMatrixInvert=tmpVectorBoneGMatrixInvert[tmpIterBegin->first];

					glm::mat4x4 tmpMat4x4BoneGMatrixInvert;
					tmpMat4x4BoneGMatrixInvert[0][0]=tmpBoneGMatrixInvert[0][0];tmpMat4x4BoneGMatrixInvert[0][1]=tmpBoneGMatrixInvert[0][1];tmpMat4x4BoneGMatrixInvert[0][2]=tmpBoneGMatrixInvert[0][2];tmpMat4x4BoneGMatrixInvert[0][3]=tmpBoneGMatrixInvert[0][3];
					tmpMat4x4BoneGMatrixInvert[1][0]=tmpBoneGMatrixInvert[1][0];tmpMat4x4BoneGMatrixInvert[1][1]=tmpBoneGMatrixInvert[1][1];tmpMat4x4BoneGMatrixInvert[1][2]=tmpBoneGMatrixInvert[1][2];tmpMat4x4BoneGMatrixInvert[1][3]=tmpBoneGMatrixInvert[1][3];
					tmpMat4x4BoneGMatrixInvert[2][0]=tmpBoneGMatrixInvert[2][0];tmpMat4x4BoneGMatrixInvert[2][1]=tmpBoneGMatrixInvert[2][1];tmpMat4x4BoneGMatrixInvert[2][2]=tmpBoneGMatrixInvert[2][2];tmpMat4x4BoneGMatrixInvert[2][3]=tmpBoneGMatrixInvert[2][3];
					tmpMat4x4BoneGMatrixInvert[3][0]=tmpBoneGMatrixInvert[3][0];tmpMat4x4BoneGMatrixInvert[3][1]=tmpBoneGMatrixInvert[3][1];tmpMat4x4BoneGMatrixInvert[3][2]=tmpBoneGMatrixInvert[3][2];tmpMat4x4BoneGMatrixInvert[3][3]=tmpBoneGMatrixInvert[3][3];

					glm::vec3& tmpVec3PositionZeroFrame=tmpVectorVertex[vertexindex].Position;

					glm::vec4 tmpVec4PositionZeroFrame;
					tmpVec4PositionZeroFrame.x = tmpVec3PositionZeroFrame.x;
					tmpVec4PositionZeroFrame.y = -tmpVec3PositionZeroFrame.z;
					tmpVec4PositionZeroFrame.z = tmpVec3PositionZeroFrame.y;
					tmpVec4PositionZeroFrame.w = 1;

					glm::vec4 tmpPositionNoBone = tmpMat4x4BoneGMatrixInvert * tmpVec4PositionZeroFrame;

					tmpOfStreamAnim.write((char*)(&tmpPositionNoBone),sizeof(tmpPositionNoBone));
				}
			}
		}
		tmpOfStreamMesh.close();
		tmpOfStreamAnim.close();
		foutLogMaterial.close();
		foutLog.close();
	}




	tmpGameScene->ReleaseIGame();

	return TRUE;
}


