using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class MouseEventHandler : MonoBehaviour, IPointerDownHandler, IBeginDragHandler, IDragHandler, IEndDragHandler
{
	void Start()
	{
	}

	public void OnPointerDown(PointerEventData eventData)
	{		
		if (eventData.button == PointerEventData.InputButton.Right) // right btn clicked
			OnRBtnDown (eventData);
		else if (eventData.button == PointerEventData.InputButton.Left)			
			OnLBtnDown (eventData);
	}

	private void OnRBtnDown(PointerEventData eventData)
	{
		int objIndex = StageDataManager.GetInstance().CreateObject (eventData.position);
        ViewManager.GetInstance().CreateObjectTile(objIndex, eventData.position);
	}

	private void OnLBtnDown(PointerEventData eventData)
	{

	}

    public void OnDrag(PointerEventData eventData)
    {
        Debug.Log("drag");
    }

    public void OnBeginDrag(PointerEventData eventData)
    {

    }

    public void OnEndDrag(PointerEventData eventData)
    {

    }
}
