using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class MovePosByDrag : MonoBehaviour, IDragHandler, IEndDragHandler
{
    public void OnDrag(PointerEventData eventData)
    {
        transform.position = Input.mousePosition;
    }

    public void OnEndDrag(PointerEventData eventData)
    {
        CellPosAmender cellPosAmender = gameObject.GetComponent<CellPosAmender>();
        ObjectInfo objInfo = StageDataManager.GetInstance().GetObjectInfoByIndex(cellPosAmender.m_index);
        objInfo.pos = eventData.position;

        ViewManager.GetInstance().SetActivatePanel(gameObject);
    }
}
