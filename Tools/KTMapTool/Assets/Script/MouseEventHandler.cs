using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class MouseEventHandler : MonoBehaviour, IPointerDownHandler
{
	// shortcuts
    Image m_bgPanel;
	ViewManager m_viewMgr;
	StageDataManager m_dataMgr;

	void Start()
	{
        m_bgPanel = GameObject.Find ("BGPanel").GetComponent<Image> ();
		m_viewMgr = m_bgPanel.GetComponent<ViewManager> ();
		m_dataMgr = GameObject.Find ("StageData").GetComponent<StageDataManager> ();
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
		int objIndex = m_dataMgr.CreateObject (eventData.position);
        m_viewMgr.CreateObjectTile(objIndex, eventData.position);
	}

	private void OnLBtnDown(PointerEventData eventData)
	{
		Debug.Log ("left clicked: not implemented. todo: select an object, activate it(maybe need outline?), and show detail view for it");
	}
}
