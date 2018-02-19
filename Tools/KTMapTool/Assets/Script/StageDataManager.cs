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
    public string texture;
    public string onCollisionScript;
	public int offsetX, offsetY;
    public bool isCollision;

	public  ObjectInfo(Vector2 pos)
	{
		this.pos = pos;
		this.type = "null";
        this.texture = "null";
        this.onCollisionScript = "null";
        this.isCollision = false;
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

	// UI shortcuts
	InputField m_widthEdit;
	InputField m_heightEdit;
	InputField m_bgTextureEdit;
    InputField m_typeEdit = null;
    InputField m_textureEdit = null;
    InputField m_onCollisionEdit = null;
    Toggle m_collisionToggle = null;

    // public static
    public static StageDataManager m_instance = null;
    public static StageDataManager GetInstance()
    {
        if(m_instance == null)
            m_instance = GameObject.Find("StageData").GetComponent<StageDataManager>();

        return m_instance;
    }

    public static int GetIndexByName(string name)
    {
        int pos = name.IndexOf("_");
        return Int32.Parse(name.Substring(pos + 1));
    }

	void Start()
	{
		m_widthEdit = GameObject.Find ("WidthEdit").GetComponent<InputField> ();
		m_heightEdit = GameObject.Find ("HeightEdit").GetComponent<InputField> ();
		m_bgTextureEdit = GameObject.Find ("BGTextureEdit").GetComponent<InputField> ();
	}
    private void InitByDefault()
    {
        m_width = DEFAULT_WIDTH;
        m_height = DEFAULT_HEIGHT;
        m_widthEdit.text = m_width.ToString();
        m_heightEdit.text = m_height.ToString();

        ViewManager.GetInstance().ResizeBGPanel(m_width, m_height);
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
        
        ViewManager.GetInstance().ResizeBGPanel(m_width, m_height);
        ViewManager.GetInstance().SetBGTexture(m_bgTextureEdit.text);
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
            objInfo.type = objElem.GetAttribute("type");
            objInfo.texture = objElem.GetAttribute("texture");
            objInfo.onCollisionScript = objElem.GetAttribute("on_collision");
            objInfo.isCollision = bool.Parse(objElem.GetAttribute("is_collision"));
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
            objElem.SetAttribute("type", objinfo.type);
            objElem.SetAttribute("texture", objinfo.texture);
            objElem.SetAttribute("on_collision", objinfo.onCollisionScript);
            objElem.SetAttribute("is_collision", objinfo.isCollision.ToString());
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

        ViewManager.GetInstance().ResizeBGPanel(m_width, m_height);
    }

    public void DrawObjects()
    {
        int index = 0;
        foreach(ObjectInfo objInfo in m_objList)
        {
            ViewManager.GetInstance().CreateObjectTile(index, objInfo.pos);
            ++index;
        }
    }

    public void Reset()
    {
        m_objList.Clear();
        DrawObjects();
    }

    public void LoadDetailInfo(GameObject gObj)
    {
        ViewManager.GetInstance().SetActivatePanel(gObj);
        int index = StageDataManager.GetIndexByName(gObj.name);
        ObjectInfo info = StageDataManager.GetInstance().GetObjectInfoByIndex(index);
        if (info == null)
        {
            MessageBox.GetInstance().Show("tile index error: " + index.ToString());
            return;
        }

        GetTypeEdit().text = info.type;
        GetTextureEdit().text = info.texture;
        GetCollisionToggle().isOn = info.isCollision;
        GetOnCollisionEdit().text = info.onCollisionScript;
    }

    public void ApplyDetailInfo()
    {
        GameObject currentActivateGameObj = ViewManager.GetInstance().GetActivatePanel();
        int index = StageDataManager.GetIndexByName(currentActivateGameObj.name);
        ObjectInfo info = GetObjectInfoByIndex(index);
        if(info == null)
        {
            MessageBox.GetInstance().Show("index error: " + index.ToString());
            return;
        }

        info.type = GetTypeEdit().text;
        info.texture = GetTextureEdit().text;
        info.onCollisionScript = GetOnCollisionEdit().text;
        info.isCollision = GetCollisionToggle().isOn;
    }

    // ui shortcuts
    InputField GetTypeEdit()
    {
        if (m_typeEdit == null)
            m_typeEdit = GameObject.Find("TypeEdit").GetComponent<InputField>();

        return m_typeEdit;
    }

    InputField GetTextureEdit()
    {
        if (m_textureEdit == null)
            m_textureEdit = GameObject.Find("TextureEdit").GetComponent<InputField>();

        return m_textureEdit;
    }

    InputField GetOnCollisionEdit()
    {
        if (m_onCollisionEdit == null)
            m_onCollisionEdit = GameObject.Find("EventEdit").GetComponent<InputField>();

        return m_onCollisionEdit;
    }

    Toggle GetCollisionToggle()
    {
        if (m_collisionToggle == null)
            m_collisionToggle = GameObject.Find("CollisionToggle").GetComponent<Toggle>();

        return m_collisionToggle;
    }    
}
