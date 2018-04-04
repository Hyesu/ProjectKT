using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CellPosAmender : MonoBehaviour 
{
	public static int CELL_SIZE = 40;
	public bool m_amended = false;
	public int m_index = 0;
    
	public void AmendActivatePanelPos(GameObject activatePanel)
	{
		ObjectInfo objInfo = StageDataManager.GetInstance().GetObjectInfoByIndex (m_index);
		if (objInfo == null) 
		{
            MessageBox.GetInstance().Show("Assert: index[" + m_index + "]");
			return;
		}

		objInfo.offsetX = (int)objInfo.pos.x / CELL_SIZE;
		objInfo.offsetY = (int)objInfo.pos.y / CELL_SIZE;
        
        int amendX = objInfo.offsetX * CELL_SIZE;
        int amendY = objInfo.offsetY * CELL_SIZE;
		objInfo.pos.x = (float)amendX;
		objInfo.pos.y = (float)amendY;

		activatePanel.transform.position = objInfo.pos;
		m_amended = true;
	}
}