using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System.IO;
using System;

using UnityEngine;
using UnityEngine.UI;

public class XmlParser : MonoBehaviour 
{
	private string GetDataFilePath(string subDir, string fileName, string extension)
	{
		string rootDirName = "ProjectKT";
		string dataPath = Application.dataPath.Substring (0, Application.dataPath.IndexOf (rootDirName) + rootDirName.Length);
		string fileDir = dataPath + "/Data/" + subDir + "/";
		string filePath = fileDir + fileName + "." + extension;

		return filePath;
	}

	public void LoadStage(string stageFileName)
	{		
		string stageFilePath = GetDataFilePath ("Stage", stageFileName, "xml");
		Debug.Log ("LoadStage: " + stageFilePath);

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
		{
			// child processing
		}
	}

	public void SaveStage(string stageFileName)
	{
		string stageFilePath = GetDataFilePath ("Stage", stageFileName, "xml");
		Debug.Log ("SaveStage: " + stageFilePath);

		GameObject stageData = GameObject.Find ("StageData");
		StageDataManager dataMgr = stageData.GetComponent<StageDataManager> ();

		StreamReader reader = new StreamReader (stageFilePath);
		string fileContents = reader.ReadToEnd ();
		reader.Close ();

		XmlDocument xmlDoc = new XmlDocument ();
		xmlDoc.LoadXml (fileContents);
		XmlNode stageNode = xmlDoc.DocumentElement;
		dataMgr.SaveStageCommonConfig (stageNode);

		xmlDoc.Save (stageFilePath);
	}
}
