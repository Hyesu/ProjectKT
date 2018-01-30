using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using UnityEngine.UI;

public class ViewManager : MonoBehaviour 
{
	private GameObject m_currentActivatePanel = null;
    private Image m_BGPanel = null;

    void Start()
    {
        m_BGPanel = GameObject.Find("BGPanel").GetComponent<Image>();
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
	}

    public void ResizeBGPanel(int destWidth, int destHeight)
    {
        //int curWidth = (int)(m_BGPanel.rectTransform.rect.right - m_BGPanel.rectTransform.rect.left);
        //int curHeight = (int)(m_BGPanel.rectTransform.rect.top - m_BGPanel.rectTransform.rect.bottom);
        //float widthDelta = destWidth - curWidth;
        //float heightDelta = destHeight - curHeight;

        m_BGPanel.rectTransform.sizeDelta = new Vector2(destWidth, destHeight);
    }
}
