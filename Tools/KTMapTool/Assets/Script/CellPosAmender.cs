﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CellPosAmender : MonoBehaviour 
{
	private const int CELL_SIZE = 40;
	public bool m_amended = false;
	public int m_index = 0;

	StageDataManager dataMgr;

	void Start()
	{
		dataMgr = GameObject.Find ("StageData").GetComponent<StageDataManager> ();
	}

	public void AmendActivatePanelPos(GameObject activatePanel)
	{
		if (dataMgr == null)
			return;

		ObjectInfo objInfo = dataMgr.GetObjectInfoByIndex (m_index);
		if (objInfo == null) 
		{
			Debug.Log ("Assert: index[" + m_index + "]");
			return;
		}

		int amendX = (int)objInfo.pos.x / CELL_SIZE * CELL_SIZE + CELL_SIZE / 2;
		int amendY = (int)objInfo.pos.y / CELL_SIZE * CELL_SIZE + CELL_SIZE / 2;
		objInfo.pos.x = (float)amendX;
		objInfo.pos.y = (float)amendY;

		activatePanel.transform.position = objInfo.pos;
		m_amended = true;
	}
}