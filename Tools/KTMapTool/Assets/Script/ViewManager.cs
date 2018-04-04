using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using UnityEngine.UI;

public class ViewManager : MonoBehaviour 
{
	private GameObject m_currentActivatePanel = null;
    private Image m_bgPanel = null;

    public static ViewManager m_instance = null;
    public static ViewManager GetInstance()
    {
        if (m_instance == null)
            m_instance = GameObject.Find("BGPanel").GetComponent<ViewManager>();

        return m_instance;
    }

    void Start()
    {
        m_bgPanel = GameObject.Find("BGPanel").GetComponent<Image>();
    }

	void Update () 
	{
		if (m_currentActivatePanel == null)
			return;

		CellPosAmender cellPosAmender = m_currentActivatePanel.GetComponent<CellPosAmender> ();
		if (cellPosAmender.m_amended == true)
			return;

		cellPosAmender.AmendActivatePanelPos (m_currentActivatePanel);
	}

	public void SetActivatePanel(GameObject panel)
	{
		m_currentActivatePanel = panel;

        CellPosAmender cellPosAmender = m_currentActivatePanel.GetComponent<CellPosAmender>();
        cellPosAmender.m_amended = false;
    }

    public GameObject GetActivatePanel()
    {
        return m_currentActivatePanel;
    }

    public void ResizeBGPanel(int width, int height)
    {
        int destWidth = width * CellPosAmender.CELL_SIZE;
        int destHeight = height * CellPosAmender.CELL_SIZE;
        m_bgPanel.rectTransform.sizeDelta = new Vector2(destWidth, destHeight);
    }

    public void ResizeTile(GameObject panel, int width, int height)
    {
        Image image = panel.GetComponent<Image>();
        if (image == null)
        {
            image = panel.AddComponent<Image>();
            image.rectTransform.pivot = new Vector2(0.0f, 0.0f);
        }

        image.rectTransform.sizeDelta = new Vector2(CellPosAmender.CELL_SIZE * width, CellPosAmender.CELL_SIZE * height);
        image.color = Color.white;
    }
    
    public void CreateObjectTile(int objIndex, Vector2 position)
    {
        string panelName = "Panel_" + objIndex.ToString();
        GameObject newPanel = new GameObject(panelName);
        CellPosAmender cellPosAmender = newPanel.AddComponent<CellPosAmender>();
        cellPosAmender.m_index = objIndex;
        
        ResizeTile(newPanel, 1, 1);
        
        newPanel.transform.SetParent(m_bgPanel.transform, false);
        newPanel.transform.position = position;        

        newPanel.AddComponent<DetailClickHandler>();
        newPanel.AddComponent<MovePosByDrag>();
        newPanel.AddComponent<ResizeByInputKey>();
        SetActivatePanel(newPanel);
    }

    public void ResetTiles()
    {
        foreach (Transform child in m_bgPanel.transform)
            GameObject.Destroy(child.gameObject);
    }

    public void SetBGTexture(string textureFileName)
    {
        string filePath = "Image/" + textureFileName.Substring(0, textureFileName.IndexOf("."));
        m_bgPanel.sprite = Resources.Load<Sprite>(filePath);        
    }
}
