using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System;

using UnityEngine;
using UnityEngine.UI;

public class ObjectInfo
{	
	public Vector2 pos;
	public int offsetX, offsetY;
	public string type;

	public  ObjectInfo(Vector2 pos)
	{
		this.pos = pos;
		this.type = "null";
	}

    public void SetOffset(int x, int y)
    {
        offsetX = x;
        offsetY = y;
    }
}

public class StageDataManager : MonoBehaviour 
{
	// common config
	private string m_bgTextureFileName = "";
	private int m_width = 0;
	private int m_height = 0;

    const int DEFAULT_WIDTH = 500;
    const int DEFAULT_HEIGHT = 500;

	// object
	List<ObjectInfo> m_objList = new List<ObjectInfo>();

	// shortcuts
	InputField m_widthEdit;
	InputField m_heightEdit;
	InputField m_bgTextureEdit;
    ViewManager m_viewMgr;

	void Start()
	{
		m_widthEdit = GameObject.Find ("WidthEdit").GetComponent<InputField> ();
		m_heightEdit = GameObject.Find ("HeightEdit").GetComponent<InputField> ();
		m_bgTextureEdit = GameObject.Find ("BGTextureEdit").GetComponent<InputField> ();
        m_viewMgr = GameObject.Find("BGPanel").GetComponent<ViewManager>();
	}
    private void InitByDefault()
    {
        m_width = DEFAULT_WIDTH;
        m_height = DEFAULT_HEIGHT;
        m_widthEdit.text = m_width.ToString();
        m_heightEdit.text = m_height.ToString();

        m_viewMgr.ResizeBGPanel(m_width, m_height);
    }

	public void LoadStageCommonConfig(XmlNode stageNode)
	{
		// size
		m_width = Int32.Parse(stageNode.Attributes["width"].Value);
		m_height = Int32.Parse(stageNode.Attributes["height"].Value);
		m_widthEdit.text = m_width.ToString();
		m_heightEdit.text = m_height.ToString();

		// back ground texture
		m_bgTextureFileName = stageNode.Attributes["bg_texture"].Value;
		m_bgTextureEdit.text = m_bgTextureFileName;
        
        m_viewMgr.ResizeBGPanel(m_width, m_height);
        m_viewMgr.SetBGTexture(m_bgTextureEdit.text);
	}
    public void LoadStageObjectInfo(XmlNode stageNode)
    {
        m_objList.Clear();
        foreach(XmlElement objElem in stageNode)
        {
            int x = Int32.Parse(objElem.GetAttribute("x"));
            int y = Int32.Parse(objElem.GetAttribute("y"));
            Vector2 position = new Vector2(x * CellPosAmender.CELL_SIZE, y * CellPosAmender.CELL_SIZE);
            ObjectInfo objInfo = new ObjectInfo(position);
            objInfo.SetOffset(x, y);
            m_objList.Add(objInfo);            
        }

        DrawObjects();
    }

	public void SaveStageCommonConfig(XmlElement stageElem)
	{
		// size
		m_width = Int32.Parse(m_widthEdit.text);
		m_height = Int32.Parse(m_heightEdit.text);
        stageElem.SetAttribute("width", m_width.ToString());
        stageElem.SetAttribute("height", m_height.ToString());

        // back ground texture
        m_bgTextureFileName = m_bgTextureEdit.text;
        stageElem.SetAttribute("bg_texture", m_bgTextureFileName);
	}
    public void SaveStageObjectInfo(XmlDocument doc, XmlElement stageElem)
    {
        int index = 0;
        foreach(ObjectInfo objinfo in m_objList)
        {
            ++index;
            XmlElement objElem = (XmlElement)stageElem.AppendChild(doc.CreateElement("Object"));
            objElem.SetAttribute("id", index.ToString());
            objElem.SetAttribute("x", objinfo.offsetX.ToString());
            objElem.SetAttribute("y", objinfo.offsetY.ToString());
        }
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

    public void SetSize(int width, int height)
    {
        m_width = width;
        m_height = height;

        m_viewMgr.ResizeBGPanel(m_width, m_height);
    }

    public void DrawObjects()
    {
        int index = 0;
        foreach(ObjectInfo objInfo in m_objList)
        {
            m_viewMgr.CreateObjectTile(index, objInfo.pos);
            ++index;
        }
    }

    public void Reset()
    {
        m_objList.Clear();
        DrawObjects();
    }
}
