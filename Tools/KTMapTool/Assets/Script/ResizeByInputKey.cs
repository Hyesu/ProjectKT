using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResizeByInputKey : MonoBehaviour
{
	void Update ()
    {
        if (Input.GetKeyUp("up"))
            ResizeActivePanel(0, 1);
        else if (Input.GetKeyUp("right"))
            ResizeActivePanel(1, 0);
        else if (Input.GetKeyUp("down"))
            ResizeActivePanel(0, -1);
        else if (Input.GetKeyUp("left"))
            ResizeActivePanel(-1, 0);
	}

    private void ResizeActivePanel(int dx, int dy)
    {
        GameObject activePanel = ViewManager.GetInstance().GetActivatePanel();
        if (activePanel == null)
            return;

        CellPosAmender cellPosAmender = activePanel.GetComponent<CellPosAmender>();
        ObjectInfo objInfo = StageDataManager.GetInstance().GetObjectInfoByIndex(cellPosAmender.m_index);
        int destX = objInfo.AddWidth(dx);
        int destY = objInfo.AddHeight(dy);

        ViewManager.GetInstance().ResizeTile(activePanel, destX, destY);
    }
}
