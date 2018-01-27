using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System;

using UnityEngine;
using UnityEngine.UI;

public class ObjectInfo
{	
	public Vector2 pos;
	public string type;

	public  ObjectInfo(Vector2 pos)
	{
		this.pos = pos;
		this.type = "null";
	}
}

public class StageDataManager : MonoBehaviour 
{
	// common config
	private string m_bgTextureFileName = "";
	private int m_width = 0;
	private int m_height = 0;

	// object
	List<ObjectInfo> m_objList = new List<ObjectInfo>();

	// shortcuts
	InputField m_widthEdit;
	InputField m_heightEdit;
	InputField m_bgTextureEdit;

	void Start()
	{
		m_widthEdit = GameObject.Find ("WidthEdit").GetComponent<InputField> ();
		m_heightEdit = GameObject.Find ("HeightEdit").GetComponent<InputField> ();
		m_bgTextureEdit = GameObject.Find ("BGTextureEdit").GetComponent<InputField> ();
	}

	public void LoadStageCommonConfig(XmlNode stageNode)
	{
		//width
		m_width = Int32.Parse(stageNode.Attributes["width"].Value);
		m_widthEdit.text = m_width.ToString();

		// height
		m_height = Int32.Parse(stageNode.Attributes["height"].Value);
		m_heightEdit.text = m_height.ToString();

		// back ground texture
		m_bgTextureFileName = stageNode.Attributes["bg_texture"].Value;
		m_bgTextureEdit.text = m_bgTextureFileName;
	}

	public void SaveStageCommonConfig(XmlNode stageNode)
	{
		//width
		m_width = Int32.Parse(m_widthEdit.text);
		stageNode.Attributes ["width"].Value = m_width.ToString();

		// height
		m_height = Int32.Parse(m_heightEdit.text);
		stageNode.Attributes ["height"].Value = m_height.ToString();

		// back ground texture
		m_bgTextureFileName = m_bgTextureEdit.text;
		stageNode.Attributes["bg_texture"].Value = m_bgTextureFileName;
	}

	public int CreateObject(Vector2 pos)
	{
		ObjectInfo obj = new ObjectInfo (pos);
		m_objList.Add (obj);
		return m_objList.IndexOf (obj);
	}

	public ObjectInfo GetObjectInfoByIndex(int index)
	{
		return m_objList[index];
	}
}
