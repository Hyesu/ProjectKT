using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class MouseEventHandler : MonoBehaviour, IPointerDownHandler
{
    Image m_bgPanel;	

	void Start()
	{
        m_bgPanel = GameObject.Find ("BGPanel").GetComponent<Image> ();
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
        Debug.Log("left clicked: not implemented. todo: by drag and drop, move tiles");
	}
}
