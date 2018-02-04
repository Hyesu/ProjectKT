﻿using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System.IO;
using System;

using UnityEngine;
using UnityEngine.UI;

public class XmlParser : MonoBehaviour 
{
	public static string GetDataFilePath(string subDir, string fileName, string extension)
	{
		string rootDirName = "ProjectKT";
		string dataPath = Application.dataPath.Substring (0, Application.dataPath.IndexOf (rootDirName) + rootDirName.Length);
		string fileDir = dataPath + "/Data/" + subDir + "/";
        string filePath = fileDir + fileName;
        if(extension.Length > 0)
            filePath = filePath + "." + extension;

		return filePath;
	}

	public void LoadStage(string stageFileName)
	{		
		string stageFilePath = GetDataFilePath ("Stage", stageFileName, "xml");		

		GameObject stageData = GameObject.Find ("StageData");
		StageDataManager dataMgr = stageData.GetComponent<StageDataManager> ();
        
		StreamReader reader = new StreamReader (stageFilePath);
		string fileContents = reader.ReadToEnd ();
		reader.Close ();

		XmlDocument xmlDoc = new XmlDocument ();
		xmlDoc.LoadXml (fileContents);
		XmlNode stageNode = xmlDoc.DocumentElement;
		dataMgr.LoadStageCommonConfig (stageNode);
        if (stageNode.HasChildNodes)
            dataMgr.LoadStageObjectInfo(stageNode);
	}

	public void SaveStage(string stageFileName)
	{
		string stageFilePath = GetDataFilePath ("Stage", stageFileName, "xml");
		GameObject stageData = GameObject.Find ("StageData");
		StageDataManager dataMgr = stageData.GetComponent<StageDataManager> ();
        
        if (File.Exists(stageFilePath))
            File.Delete(stageFilePath);

        CreateEmptyXmlFile(stageFilePath, "Stage");

        StreamReader reader = new StreamReader (stageFilePath);
		string fileContents = reader.ReadToEnd ();
		reader.Close ();

		XmlDocument xmlDoc = new XmlDocument ();
		xmlDoc.LoadXml (fileContents);
		XmlElement stageElem = xmlDoc.DocumentElement;
		dataMgr.SaveStageCommonConfig (stageElem);
        dataMgr.SaveStageObjectInfo(xmlDoc, stageElem);

		xmlDoc.Save (stageFilePath);
	}

    private void CreateEmptyXmlFile(string filePath, string rootName)
    {
        XmlDocument doc = new XmlDocument();
        XmlDeclaration xmlDeclaration = doc.CreateXmlDeclaration("1.0", "UTF-8", null);
        doc.AppendChild(xmlDeclaration);

        XmlElement root = doc.CreateElement(rootName);
        doc.AppendChild(root);

        File.WriteAllText(filePath, doc.OuterXml);
    }
}
