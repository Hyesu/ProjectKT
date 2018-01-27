using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using UnityEngine.UI;

public class ViewManager : MonoBehaviour 
{
	private GameObject m_currentActivatePanel = null;	

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
}
