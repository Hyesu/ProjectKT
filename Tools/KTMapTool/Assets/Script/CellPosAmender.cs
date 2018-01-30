using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CellPosAmender : MonoBehaviour 
{
	private const int CELL_SIZE = 40;
	public bool m_amended = false;
	public int m_index = 0;

	StageDataManager m_dataMgr;
    MessageBox m_msgBox;

	void Start()
	{
        m_dataMgr = GameObject.Find ("StageData").GetComponent<StageDataManager> ();
        m_msgBox = GameObject.Find("MessageBox").GetComponent<MessageBox>();
	}

	public void AmendActivatePanelPos(GameObject activatePanel)
	{
		if (m_dataMgr == null)
			return;

		ObjectInfo objInfo = m_dataMgr.GetObjectInfoByIndex (m_index);
		if (objInfo == null) 
		{
            m_msgBox.Show("Assert: index[" + m_index + "]");
			return;
		}

		objInfo.offsetX = (int)objInfo.pos.x / CELL_SIZE;
		objInfo.offsetY = (int)objInfo.pos.y / CELL_SIZE;

		int amendX = objInfo.offsetX * CELL_SIZE + CELL_SIZE / 2;
		int amendY = objInfo.offsetY * CELL_SIZE + CELL_SIZE / 2;
		objInfo.pos.x = (float)amendX;
		objInfo.pos.y = (float)amendY;

		activatePanel.transform.position = objInfo.pos;
		m_amended = true;
	}
}