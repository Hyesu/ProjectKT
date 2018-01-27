using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System;

using UnityEngine;
using UnityEngine.UI;

public class StageDataManager : MonoBehaviour 
{
	// datas
//	private string m_stageFilePath = "";
//	private string m_bgTextureFileName = "";
//	private int m_width = 0;
//	private int m_height = 0;

	public void LoadStageCommonConfig(XmlNode stageNode)
	{
		//width
		int width = Int32.Parse(stageNode.Attributes["width"].Value);
		GameObject widthEdit = GameObject.Find ("WidthEdit");
		InputField _widthEdit = widthEdit.GetComponent<InputField> ();
		_widthEdit.text = width.ToString();

		// height
		int height = Int32.Parse(stageNode.Attributes["height"].Value);
		GameObject heightEdit = GameObject.Find ("HeightEdit");
		InputField _heightEdit = heightEdit.GetComponent<InputField> ();
		_heightEdit.text = height.ToString();

		// back ground texture
		string bgTextureFileName = stageNode.Attributes["bg_texture"].Value;
		GameObject bgTextureEdit = GameObject.Find ("BGTextureEdit");
		InputField _bgTextureEdit = bgTextureEdit.GetComponent<InputField> ();
		_bgTextureEdit.text = bgTextureFileName;
	}

	public void SaveStageCommonConfig(XmlNode stageNode)
	{
		//width
		GameObject widthEdit = GameObject.Find ("WidthEdit");
		InputField _widthEdit = widthEdit.GetComponent<InputField> ();
		int width = Int32.Parse(_widthEdit.text);
		stageNode.Attributes ["width"].Value = width.ToString();

		// height
		GameObject heightEdit = GameObject.Find ("HeightEdit");
		InputField _heightEdit = heightEdit.GetComponent<InputField> ();
		int height = Int32.Parse(_heightEdit.text);
		stageNode.Attributes ["height"].Value = height.ToString();

		// back ground texture
		GameObject bgTextureEdit = GameObject.Find ("BGTextureEdit");
		InputField _bgTextureEdit = bgTextureEdit.GetComponent<InputField> ();
		string bgTextureFileName = _bgTextureEdit.text;
		stageNode.Attributes["bg_texture"].Value = bgTextureFileName;
	}
}
